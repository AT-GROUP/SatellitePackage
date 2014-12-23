#include "QSatelliteItem.h"
#include "InfoTableModel.h"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QHeaderView>
#include <tuple>

QSatelliteItem::QSatelliteItem(Satellite *satellite, QObject *parent)
    :QObject(parent),QGraphicsItemGroup()
{
    icon = new QGraphicsPixmapItem(QPixmap(":satellite"));
	addToGroup(icon);
    pSatellite = satellite;

    setPos(*pSatellite->pos());
    setAcceptHoverEvents(true);
    icon->setVisible (true);

    QString n = pSatellite->name();

    pInfoList = new QTableView();
    pInfoList->setModel(new InfoTableModel());
    pInfoList->setAutoScroll (false);
    pInfoList->horizontalHeader()->hide();
    pInfoList->verticalHeader()->hide();

    connect(pSatellite,SIGNAL(attrChanged(const StrPair&)),this,SLOT(updateFact(const StrPair&)), Qt::QueuedConnection);
    pSatellite->refreshData();
}

QSatelliteItem::~QSatelliteItem()
{
	delete icon;
    delete pInfoList->model();
    delete pInfoList;
}

void QSatelliteItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (acceptHoverEvents())
    {
        setAcceptHoverEvents(false);
        event->accept();
        return;
    }
    setAcceptHoverEvents(true);
    event->accept();
}

void QSatelliteItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event)
{
   // ToDo: Fix warning "QGraphicsProxyWidget::setWidget: cannot embed widget *XXXXX; already embedded"
   proxy = icon->scene()->addWidget(pInfoList);
   proxy->setPos(event->scenePos());
   proxy->resize (190,190);

   pInfoList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   pInfoList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   pInfoList->show();

   event->accept();
}

void QSatelliteItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event)
{    
    pInfoList->hide();
    event->accept();
}

void QSatelliteItem::updateFact(const StrPair& info)
{
    QString attrName = info.first, attrValue = info.second;
    InfoTableModel* tempModel = (InfoTableModel*) pInfoList->model();
    if (attrName == "Name")
    {
        tempModel->updateData(std::make_tuple(0,attrName,attrValue));
    }
    if (attrName == "IpAddress")
    {
        tempModel->updateData(std::make_tuple(1,attrName,attrValue));
    }
    if (attrName == "MaxBw")
    {
        emit valueChanged(pSatellite->name() + " " + attrName + " changed to " + attrValue);
        tempModel->updateData(std::make_tuple(2,attrName,attrValue));
    }
    if (attrName == "CurBw")
    {
        emit valueChanged(pSatellite->name() + " " + attrName + " changed to " + attrValue);
        tempModel->updateData(std::make_tuple(3,attrName,attrValue));
    }
    if (attrName == "StationCount")
    {
        tempModel->updateData(std::make_tuple(4,attrName,attrValue));
    }
    if (attrName == "Status")
    {
        emit valueChanged(pSatellite->name() + " " + attrName + " changed to " + attrValue);
        tempModel->updateData(std::make_tuple(5,attrName,attrValue));
    }
}

Satellite * QSatelliteItem::satellite() const
{
    return pSatellite;
}
