#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>
#include "StatisticCollector.h"
#include "qcustomplot.h"

class GraphicsWidget : public QCustomPlot
{
    Q_OBJECT
private:
    Data* statisticsData;
    Satellite* sat;

    void refreshGraphData();
public:
    explicit GraphicsWidget(StatisticCollector* sc, Satellite* sat, QWidget *parent = 0);

signals:

public slots:
    void updateGraph();

};

#endif // GRAPHICSWIDGET_H
