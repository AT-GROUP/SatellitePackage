#include "GraphicsWidget.h"

GraphicsWidget::GraphicsWidget(StatisticCollector *sc, Satellite *sat, QWidget *parent) :
    QCustomPlot(parent)
{
    statisticsData = sc->getData(sat);
    this->sat = sat;
    QCPItemText* satName = new QCPItemText(this);
    addItem(satName);
    satName->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    satName->position->setType(QCPItemPosition::ptAxisRectRatio);
    satName->position->setCoords(0.5, 0);
    satName->setText(sat->name());
    //satName->setText(QString::number(statisticsData->first.size()));
    satName->setFont(QFont(font().family(), 16));
    satName->setPen(QPen(Qt::black));
    addGraph();
    refreshGraphData();
    xAxis->setLabel("Time");
    xAxis->setTickLabelType(QCPAxis::LabelType::ltDateTime);
    yAxis->setLabel("curBw");
    setMinimumSize(400, 300);
    connect(sc, SIGNAL(dataUpdated()), this, SLOT(updateGraph()));
}

void GraphicsWidget::updateGraph()
{
    refreshGraphData();
    replot();
}

void GraphicsWidget::refreshGraphData()
{
    graph(0)->setData(statisticsData->first, statisticsData->second);
    xAxis->setRange(statisticsData->first.front(), statisticsData->first.back());
    yAxis->setRange(0, 1.1 * sat->maxBw());
}
