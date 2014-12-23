#ifndef REALSTATISTICCOLLECTOR_H
#define REALSTATISTICCOLLECTOR_H

#include <unordered_map>
#include <list>
#include "RealSatellite.h"
//#include "../../src/Model/model.h"
#include <QVector>
#include <QTimer>

typedef double Time;
typedef double Value;
typedef QVector<Time> Times; //using QVector<double> because of QCustomPlot
typedef QVector<Value> Values;
typedef std::pair<Times, Values> Data;

class RealStatisticCollector : public QObject
{
    Q_OBJECT
private:
    std::unordered_map<RealSatellite*, Data> statistics;
    QTimer* timer; //using this timer temporary
    Time time;
public:
    RealStatisticCollector(QVector<RealSatellite*>* satellites, Time t);
    void start(); //listen to timer and collect data
    void pause(); //use when simulation is paused
    void addData(RealSatellite* sat, Time t);
    Data* getData(RealSatellite* sat);
public slots:
    void fetchData();
signals:
    void dataUpdated();
};


#endif // REALSTATISTICCOLLECTOR_H
