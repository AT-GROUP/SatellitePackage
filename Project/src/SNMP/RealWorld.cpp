#include "RealWorld.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <iostream>

RealWorld::RealWorld()
{
    rp = new RouterPool();
    timer = new QTimer(this);
    satellites = QVector<RealSatellite*>();
    stations = QVector<RealStation*>();
    loadInitData();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void RealWorld::start()
{
    timer->start(rp->getInterval());
}

void RealWorld::stop()
{
    timer->stop();
}

void RealWorld::update()
{
    rp->updateRouters();
    for(RealSatellite* sat : satellites)
    {
        sat->setCurInBw(0);
        sat->setCurOutBw(0);
    }
    for(RealStation* station : stations)
    {
        station->satellite()->incCurInBw(station->outBwInUse());
        station->satellite()->incCurOutBw(station->inBwInUse());
    }
    //qDebug() << "Satellite " << satellites.front()->name() << " : " << satellites.front()->curInBw() << ", " << satellites.front()->curOutBw();
    //qDebug() << "Satellite " << satellites.back()->name() << " : " << satellites.back()->curInBw() << ", " << satellites.back()->curOutBw();
}

void RealWorld::loadInitData()
{
    QFile* pFile = new QFile("init2.xml");
    if (!pFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QXmlStreamReader xml(pFile);
    while ((!xml.atEnd()) && (!xml.hasError()))
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            QXmlStreamAttributes attrs = xml.attributes();
            if (xml.name() == "satellite")
                satellites.push_back(new RealSatellite(attrs.value("name").toString(), attrs.value("maxBw").toInt(), attrs.value("maxBw").toInt()));
            if (xml.name() == "station")
            {
                QString ip = attrs.value("ip").toString();
                rp->addRouter(ip);
                SnmpRouter* r = rp->getRouter(ip);
                QString _interface = attrs.value("interface").toString();
                r->selectInterface(_interface.toInt());
                stations.push_back(new RealStation(attrs.value("name").toString(), satellites.back(), r));
            }
            if (xml.name() == "interval")
            {
                rp->setInterval(attrs.value("value").toInt());
            }
        }
    }
    pFile->close();
    delete pFile;
}

QVector<RealSatellite*>* RealWorld::satelliteList()
{
    return &satellites;
}

QVector<RealStation*>* RealWorld::stationList()
{
    return &stations;
}
