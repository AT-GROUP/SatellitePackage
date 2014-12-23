#ifndef REALSTATIONDATATABLE_H
#define REALSTATIONDATATABLE_H

#include "../SNMP/RealWorld.h"
#include "../SNMP/RealStatisticCollector.h"

#include <QTableWidget>

class RealStationDataTable : public QTableWidget
{
    Q_OBJECT
private:
    QVector<RealStation*> stations;
    RealSatellite* sat;
    RealWorld* mod;
public:
    explicit RealStationDataTable(RealStatisticCollector* sc, RealSatellite* sat, RealWorld* mod,QWidget *parent = 0);

signals:

public slots:
    void refreshData();

};

#endif // REALSTATIONDATATABLE_H
