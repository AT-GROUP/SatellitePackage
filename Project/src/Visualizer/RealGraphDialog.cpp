#include "RealGraphDialog.h"
#include <QBoxLayout>

RealGraphDialog::RealGraphDialog(RealWorld* mod, RealStatisticCollector *sc, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* outerLayout = new QVBoxLayout;
    //curBw
    QHBoxLayout* graphicsLayout = new QHBoxLayout;
    QVector<RealSatellite*>* satellites = mod->satelliteList();
    for(auto sat = satellites->begin(); sat != satellites->end(); ++sat)
    {
        RealGraphicsWidget* gw = new RealGraphicsWidget(sc, *sat, this);
        graphicsLayout->addWidget(gw);
    }
    outerLayout->addLayout(graphicsLayout);

    //tables
    QHBoxLayout* tablesLayout = new QHBoxLayout;
    for(auto sat = satellites->begin(); sat != satellites->end(); ++sat)
    {
        RealStationDataTable* tw = new RealStationDataTable(sc, *sat, mod, this);
        tablesLayout->addWidget(tw);
    }
    outerLayout->addLayout(tablesLayout);

    setLayout(outerLayout);
    resize(1280, 700);
}
