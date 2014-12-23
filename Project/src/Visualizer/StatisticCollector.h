#ifndef STATISTICCOLLECTOR_H
#define STATISTICCOLLECTOR_H

#include <unordered_map>
#include <list>
#include "../../src/Model/model.h"
#include <QVector>
#include <QTimer>

typedef double Time;
typedef double Value;
typedef QVector<Time> Times; //using QVector<double> because of QCustomPlot
typedef QVector<Value> Values;
typedef std::pair<Times, Values> Data;

class StatisticCollector : public QObject
{
    Q_OBJECT
private:
    std::unordered_map<Satellite*, Data> statistics;
    QTimer* timer; //using this timer temporary
    Time time;
public:
    StatisticCollector(QVector<Satellite*>* satellites, Time t);
    void start(); //listen to timer and collect data
    void pause(); //use when simulation is paused
    void addData(Satellite* sat, Time t);
    Data* getData(Satellite* sat);
public slots:
    void fetchData();
signals:
    void dataUpdated();
};

#endif // STATISTICCOLLECTOR_H
