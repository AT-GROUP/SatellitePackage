#ifndef STATIONDATATABLE_H
#define STATIONDATATABLE_H

#include "../../src/Model/model.h"
#include "StatisticCollector.h"

#include <QTableWidget>

class StationDataTable : public QTableWidget
{
    Q_OBJECT
private:
    QVector<Station*> stations;
    Satellite* sat;
    Model* mod;
public:
    explicit StationDataTable(StatisticCollector* sc, Satellite* sat, Model* mod,QWidget *parent = 0);

signals:

public slots:
    void refreshData();

};

#endif // STATIONDATATABLE_H
