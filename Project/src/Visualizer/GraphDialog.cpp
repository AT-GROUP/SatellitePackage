#include "GraphDialog.h"
#include <QBoxLayout>

GraphDialog::GraphDialog(Model* mod, StatisticCollector *sc, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* outerLayout = new QVBoxLayout;
    //curBw
    QHBoxLayout* graphicsLayout = new QHBoxLayout;
    QVector<Satellite*>* satellites = mod->satelliteList();
    for(auto sat = satellites->begin(); sat != satellites->end(); ++sat)
    {
        GraphicsWidget* gw = new GraphicsWidget(sc, *sat, this);
        graphicsLayout->addWidget(gw);
    }
    outerLayout->addLayout(graphicsLayout);

    //tables
    QHBoxLayout* tablesLayout = new QHBoxLayout;
    for(auto sat = satellites->begin(); sat != satellites->end(); ++sat)
    {
        StationDataTable* tw = new StationDataTable(sc, *sat, mod, this);
        tablesLayout->addWidget(tw);
    }
    outerLayout->addLayout(tablesLayout);

    setLayout(outerLayout);
    resize(1280, 700);
}
