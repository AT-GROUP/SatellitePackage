#ifndef SNMPROUTER_H
#define SNMPROUTER_H

#include <string>
#include <list>
#include <QString>
#define STDCXX_98_HEADERS
#include "../snmp_pp/snmp_pp.h"

class RouterPool;

using namespace std;
using namespace Snmp_pp;

class SnmpRouter
{
private:
    QString ip;
    int _interface;
    long long ifInOctets, ifOutOctets;
    long long ifInBw, ifOutBw;
    RouterPool* rp;
    qint64 lastQuery;
    Snmp* snmp;
    Pdu pdu;
    Vb vb_ifInOctets, vb_ifOutOctets;
    CTarget ctarget;
public:
    explicit SnmpRouter(QString &ip, RouterPool* rp);
    ~SnmpRouter();
    void selectInterface(int index);
    long long getBw();
    long long getInOctets();
    long long getOutOctets();
    long long getInBw();
    long long getOutBw();
    void update();
    QString getIp();
};

#endif // SNMPROUTER_H
