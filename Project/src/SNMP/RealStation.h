#ifndef REALSTATION_H
#define REALSTATION_H

#include "SnmpRouter.h"
#include "RealSatellite.h"
#include <QString>

class RealStation
{
private:
    SnmpRouter* router;
    QString _name;
    RealSatellite* sat;
public:
    RealStation(QString _name, RealSatellite* sat, SnmpRouter* router);
    int inBwInUse();
    int outBwInUse();
    int bwInUse();
    SnmpRouter* getRouter();
    RealSatellite* satellite();
    QString name();
    QString ipAddress();

};

#endif // REALSTATION_H
