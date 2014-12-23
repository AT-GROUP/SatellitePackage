#include "RealStation.h"

RealStation::RealStation(QString name, RealSatellite *sat, SnmpRouter *router) : router(router), _name(name), sat(sat)
{
}

int RealStation::inBwInUse()
{
    return router->getInBw();
}

int RealStation::outBwInUse()
{
    return router->getOutBw();
}

int RealStation::bwInUse()
{
    return router->getBw();
}

SnmpRouter* RealStation::getRouter()
{
    return router;
}

RealSatellite* RealStation::satellite()
{
    return sat;
}

QString RealStation::name()
{
    return _name;
}

QString RealStation::ipAddress()
{
    return router->getIp();
}
