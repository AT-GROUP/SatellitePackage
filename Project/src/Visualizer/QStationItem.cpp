#include "QStationItem.h"
#include "InfoTableModel.h"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QHeaderView>
#include <tuple>

QStationItem::QStationItem(Station *station, QObject* parent)
    :QObject(parent),QGraphicsItemGroup()
{
    pStation = station;
    pEllipse = new QGraphicsEllipseItem(QRectF(-5,-5,5,5));
    pEllipse->setPen(QColor(Qt::red));
    addToGroup(pEllipse);
    setPos(*pStation->pos());
    setAcceptHoverEvents(true);

    pInfoList = new QTableView();
    pInfoList->setModel(new InfoTableModel());
    pInfoList->setAutoScroll (false);
    pInfoList->horizontalHeader()->hide();
    pInfoList->verticalHeader()->hide();
    connect(pStation,SIGNAL(attrChanged(const StrPair&)),this,SLOT(updateFact(const StrPair&)), Qt::QueuedConnection);
    pStation->refreshData();
}

QStationItem::~QStationItem()
{
    delete pEllipse;
    delete pInfoList->model();
    delete pInfoList;
}

void QStationItem::updateColor()
{
    QString status = pStation->status();
    if (status == "Calling")
    {
        setColor(Qt::red);
        return;
    }
    if (status == "StandBy")
    {
        setColor(Qt::yellow);
        return;
    }
    if (status == "Online")
    {
        setColor(Qt::green);
        return;
    }
    if (status == "Offline")
    {
        setColor(Qt::black);
        return;
    }
    if (status == "Connected")
    {
        setColor(Qt::blue);
        return;
    }
    setColor(Qt::transparent);
}

void QStationItem::setColor(QColor qColor)
{
    pEllipse->setBrush((QBrush(qColor)));
}

void QStationItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void QStationItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event)
{
   // ToDo: Fix warning "QGraphicsProxyWidget::setWidget: cannot embed widget *XXXXX; already embedded"
   proxy = pEllipse->scene()->addWidget(pInfoList);
   proxy->setPos(event->scenePos());
   proxy->resize (190,190);

   pInfoList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   pInfoList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   pInfoList->show();

   event->accept();
}

void QStationItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event)
{    
    pInfoList->hide();
    event->accept();
}

void QStationItem::updateFact(const StrPair& info)
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
    if (attrName == "BwInUse")
    {
        emit valueChanged(pStation->name() + " " + attrName + " changed to " + attrValue);
        tempModel->updateData(std::make_tuple(2,attrName,attrValue));
    }
    if (attrName == "BwNeeded")
    {
        emit valueChanged(pStation->name() + " " + attrName + " changed to " + attrValue);
        tempModel->updateData(std::make_tuple(3,attrName,attrValue));
    }
    if (attrName == "Satellite")
    {
        tempModel->updateData(std::make_tuple(4,attrName,attrValue));
    }
    if (attrName == "Status")
    {
        emit valueChanged(pStation->name() + " " + attrName + " changed to " + attrValue);
        updateColor();
        tempModel->updateData(std::make_tuple(5,attrName,attrValue));
    }
}

Station * QStationItem::station() const
{
    return pStation;
}
