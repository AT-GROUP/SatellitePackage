#include "RouterPool.h"
#include <sstream>
#include <QProcess>
#include <QDebug>

const long long MAX_32BIT = 4294967296;

SnmpRouter::SnmpRouter(QString& ip, RouterPool *rp): ip(ip),_interface(0),ifInOctets(-1),ifOutOctets(-1),ifInBw(0),ifOutBw(0),rp(rp)
{}

std::list<std::string> &split(const std::string &s, char delim, std::list<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

QString SnmpRouter::getIp()
{
    return ip;
}

std::list<std::string> split(const std::string &s, char delim)
{
    std::list<std::string> elems;
    split(s, delim, elems);
    return elems;
}

list<string> SnmpRouter::getInterfaceList()
{
    list<string> res;
    QString snmpProgram = "snmpwalk";
    QStringList params;
    params << "-c" <<  "public" <<
           "-v" << "2c" << ip <<
           ".1.3.6.1.2.1.2.2.1.2";
    QProcess* snmp = new QProcess();
    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    char buf[256];
    if(snmp->exitCode())
    {
        qDebug() << "Error";
        qDebug() << snmp->readAllStandardError();
        return list<string>();
    }
    while(snmp->canReadLine())
    {
        snmp->readLine(buf, sizeof(buf));
        res.push_back(split(string(buf), ' ').back());
    }
    delete snmp;
    return res;
}

void SnmpRouter::selectInterface(int index)
{
    _interface = index;
}

void SnmpRouter::update()
{
    int timeDelta = rp->getInterval();
    QString snmpProgram = "snmpget";
    QStringList params;
    QString ifOctetsMIBforInterface = ".1.3.6.1.2.1.2.2.1.10." +
            QString::number(_interface);
    params << "-c" <<  "public" <<
           "-v" << "2c" << ip <<
           ifOctetsMIBforInterface;
    QProcess* snmp = new QProcess();

    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    char buf[256];
    if(snmp->exitCode())
    {
        qDebug() << "Error";
        qDebug() << snmp->readAllStandardError();
        return;
    }
    snmp->readLine(buf, sizeof(buf));
    long long ifInOctets = atoll(split(string(buf), ' ').back().c_str());
    if(this->ifInOctets == -1)
        this->ifInOctets = ifInOctets;
    if(ifInOctets < this->ifInOctets)
        this->ifInOctets -= MAX_32BIT;
    ifInBw = (ifInOctets - this->ifInOctets)*1000 / timeDelta;
    this->ifInOctets = ifInOctets;
    //qDebug() << snmpProgram << " " << params << " ====> " << this->ifInOctets;
    delete snmp;

    ifOctetsMIBforInterface = ".1.3.6.1.2.1.2.2.1.16." +
            QString::number(_interface);
    params.clear();
    params << "-c" <<  "public" <<
           "-v" << "2c" << ip <<
           ifOctetsMIBforInterface;
    snmp = new QProcess();
    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    if(snmp->exitCode())
    {
        qDebug() << "Error";
        qDebug() << snmp->readAllStandardError();
        return;
    }
    snmp->readLine(buf, sizeof(buf));
    long long ifOutOctets = atoll(split(string(buf), ' ').back().c_str());
    if(this->ifOutOctets == -1)
        this->ifOutOctets = ifOutOctets;
    if(ifOutOctets < this->ifOutOctets)
        this->ifOutOctets -= MAX_32BIT;
    ifOutBw = (ifOutOctets - this->ifOutOctets)*1000 / timeDelta;
    this->ifOutOctets = ifOutOctets;
    //qDebug() << snmpProgram << " " << params << " ====> " << this->ifOutOctets;
    delete snmp;
}

long long SnmpRouter::getInOctets()
{
    return ifInOctets;
}

long long SnmpRouter::getOutOctets()
{
    return ifOutOctets;
}

long long SnmpRouter::getInBw()
{
    return ifInBw * 8 / 1024;
}

long long SnmpRouter::getOutBw()
{
    return ifOutBw * 8 / 1024;
}

long long SnmpRouter::getBw()
{
    return std::max(ifInBw, ifOutBw) * 8 / 1024; //kbit / s
}
