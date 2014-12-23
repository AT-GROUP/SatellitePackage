#include "RealStationDataTable.h"
#include <QStringList>
#include <cstdio> //for debug
#include <QHeaderView>

RealStationDataTable::RealStationDataTable(RealStatisticCollector* sc, RealSatellite *sat, RealWorld *mod, QWidget *parent) :
    QTableWidget(parent)
{
    this->sat = sat;
    this->mod = mod;
    setColumnCount(3);
    QStringList captions;
    captions << "Name" << "IpAddress" << "BwInUse";
    setHorizontalHeaderLabels(captions);
    resizeColumnsToContents();
    //horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

    refreshData();
    connect(sc, SIGNAL(dataUpdated()), this, SLOT(refreshData()));
}

void RealStationDataTable::refreshData()
{
    model()->removeRows(0, rowCount());
    for(auto station = mod->stationList()->begin(); station != mod->stationList()->end(); ++station)
    {
        if((*station)->satellite() == sat)
        {
            insertRow(0);
            //printf("For satellite %s added station %s\n", sat->name().toLocal8Bit().data(), (*station)->name().toLocal8Bit().data());
            setItem(0, 0, new QTableWidgetItem((*station)->name()));
            setItem(0, 1, new QTableWidgetItem((*station)->ipAddress()));
            setItem(0, 2, new QTableWidgetItem(QString::number((*station)->bwInUse())));
        }
    }
}
