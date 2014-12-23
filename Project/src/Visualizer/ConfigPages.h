#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <../../src/Model/satellite.h>
#include <../../src/Model/station.h>

class CommonSettings : public QWidget
{
    public:
        CommonSettings(QWidget *parent = 0);
};

class SatelliteSettings : public QWidget
{
    public:
        SatelliteSettings(QVector<Satellite*> *pSatelliteList, QWidget *parent = 0);
};

class StationSettings : public QWidget
{
    public:
        StationSettings(QVector<Station*> *pStationList, QVector<Satellite*> *pSatelliteList, QWidget *parent = 0);
};

#endif
