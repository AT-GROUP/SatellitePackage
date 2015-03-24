#include "RouterPool.h"
//#include <iostream>
#include <QtConcurrent/QtConcurrent>

void updateRouter(SnmpRouter* router)
{
    router->update();
    //cout << "router " << router->getIp() << " : " << router->getBw() << endl;
}

void updateAllRouters(QMap<QString, SnmpRouter*> routers)
{
    for(auto it : routers)
        updateRouter(it);
}

RouterPool::RouterPool() : interval(1000)
{
    Snmp::socket_startup();
}

void RouterPool::setInterval(int interval)
{
    this->interval = interval;
}

int RouterPool::getInterval()
{
    return interval;
}

void RouterPool::addRouter(QString ip)
{
    //cout << "Adding router " << router->getIp() << endl;
    routers.insert(ip, new SnmpRouter(ip, this));
}

SnmpRouter* RouterPool::getRouter(QString ip)
{
    return routers[ip];
}

void RouterPool::updateRouters()
{
    QtConcurrent::run(updateAllRouters, routers);
}
