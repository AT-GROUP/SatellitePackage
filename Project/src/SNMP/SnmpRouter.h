#ifndef SNMPROUTER_H
#define SNMPROUTER_H

#include <string>
#include <list>
#include <QString>

class RouterPool;

using namespace std;

class SnmpRouter
{
private:
    QString ip;
    int _interface;
    long long ifInOctets, ifOutOctets;
    long long ifInBw, ifOutBw;
    RouterPool* rp;
public:
    explicit SnmpRouter(QString &ip, RouterPool* rp);
    list<string> getInterfaceList();
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
