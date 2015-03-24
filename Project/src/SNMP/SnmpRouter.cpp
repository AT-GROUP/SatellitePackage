#include "RouterPool.h"
#include <sstream>
#include <QProcess>
#include <QDebug>
#include <QDateTime>

const long long MAX_32BIT = 4294967296;

SnmpRouter::SnmpRouter(QString& ip, RouterPool *rp): ip(ip),_interface(0),ifInOctets(-1),ifOutOctets(-1),ifInBw(0),ifOutBw(0),rp(rp),lastQuery(0)
{
    int status;
    snmp = new Snmp(status);
    if(status != SNMP_CLASS_SUCCESS)
    {
        qDebug() << snmp->error_msg(status);
    }
    ctarget = CTarget((IpAddress)ip.toStdString().c_str());
    vb_ifInOctets = Vb(".1.3.6.1.2.1.2.2.1.10.1");
    vb_ifOutOctets = Vb(".1.3.6.1.2.1.2.2.1.16.1");
    pdu += vb_ifInOctets;
    pdu += vb_ifOutOctets;
}

SnmpRouter::~SnmpRouter()
{
    delete snmp;
}

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

void SnmpRouter::selectInterface(int index)
{
    pdu.clear();
    _interface = index;
    vb_ifInOctets = Vb((string(".1.3.6.1.2.1.2.2.1.10.") + std::to_string(index)).c_str());
    vb_ifOutOctets = Vb((string(".1.3.6.1.2.1.2.2.1.16.") + std::to_string(index)).c_str());
    pdu += vb_ifInOctets;
    pdu += vb_ifOutOctets;
}

void SnmpRouter::update()
{
    int timeDelta;
    if(lastQuery == 0)
        timeDelta = rp->getInterval();
    else
        timeDelta = QDateTime::currentMSecsSinceEpoch() - lastQuery;
    lastQuery = QDateTime::currentMSecsSinceEpoch();
    int status;
    if ((status = snmp->get(  pdu, ctarget)) != SNMP_CLASS_SUCCESS)
    {
        qDebug() << snmp->error_msg( status);
    }
    else
    {
        pdu.get_vb(vb_ifInOctets, 0);
        pdu.get_vb(vb_ifOutOctets, 0);
        unsigned long ifInOctets;
        vb_ifInOctets.get_value(ifInOctets);
        if(this->ifInOctets == -1)
            this->ifInOctets = ifInOctets;
        if(ifInOctets < (unsigned long)this->ifInOctets)
            this->ifInOctets -= MAX_32BIT;
        ifInBw = (ifInOctets - this->ifInOctets)*1000 / timeDelta;
        unsigned long ifOutOctets;
        vb_ifOutOctets.get_value(ifOutOctets);
        if(this->ifOutOctets == -1)
            this->ifOutOctets = ifOutOctets;
        if(ifOutOctets < (unsigned long)this->ifOutOctets)
            this->ifOutOctets -= MAX_32BIT;
        ifOutBw = (ifOutOctets - this->ifOutOctets)*1000 / timeDelta;
        this->ifOutOctets = ifOutOctets;
        this->ifInOctets = ifInOctets;
    }
    //QString snmpProgram = "snmpget";
    //QStringList params;
    //QString ifOctetsMIBforInterface = ".1.3.6.1.2.1.2.2.1.10." +
    //        QString::number(_interface);
    //params << "-c" <<  "public" <<
    //       "-v" << "2c" << ip <<
    //       ifOctetsMIBforInterface;
    //QProcess* snmp = new QProcess();

    //snmp->start(snmpProgram, params);
    //snmp->waitForFinished();
    //char buf[256];
    //if(snmp->exitCode())
    //{
    //    qDebug() << "Error";
    //    qDebug() << snmp->readAllStandardError();
    //    return;
    //}
    //snmp->readLine(buf, sizeof(buf));
    //long long ifInOctets = atoll(split(string(buf), ' ').back().c_str());
    //if(this->ifInOctets == -1)
    //    this->ifInOctets = ifInOctets;
    //if(ifInOctets < this->ifInOctets)
    //    this->ifInOctets -= MAX_32BIT;
    //ifInBw = (ifInOctets - this->ifInOctets)*1000 / timeDelta;
    //this->ifInOctets = ifInOctets;
    ////qDebug() << snmpProgram << " " << params << " ====> " << this->ifInOctets;
    //delete snmp;

    //ifOctetsMIBforInterface = ".1.3.6.1.2.1.2.2.1.16." +
    //        QString::number(_interface);
    //params.clear();
    //params << "-c" <<  "public" <<
    //       "-v" << "2c" << ip <<
    //       ifOctetsMIBforInterface;
    //snmp = new QProcess();
    //snmp->start(snmpProgram, params);
    //snmp->waitForFinished();
    //if(snmp->exitCode())
    //{
    //    qDebug() << "Error";
    //    qDebug() << snmp->readAllStandardError();
    //    return;
    //}
    //snmp->readLine(buf, sizeof(buf));
    //long long ifOutOctets = atoll(split(string(buf), ' ').back().c_str());
    //if(this->ifOutOctets == -1)
    //    this->ifOutOctets = ifOutOctets;
    //if(ifOutOctets < this->ifOutOctets)
    //    this->ifOutOctets -= MAX_32BIT;
    //ifOutBw = (ifOutOctets - this->ifOutOctets)*1000 / timeDelta;
    //this->ifOutOctets = ifOutOctets;
    // //qDebug() << snmpProgram << " " << params << " ====> " << this->ifOutOctets;
    //delete snmp;
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
