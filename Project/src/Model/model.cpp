#include "model.h"
#include <QFile>
#include <QXmlStreamReader>
#include <random>

Model::Model(QObject *parent)
{
    Q_UNUSED(parent);
    pSatelliteList = new QVector<Satellite*>();
    pStationList = new QVector<Station*>();
    pSettingsList = new QVector<QString>();
    tact = 0;
    loadInitState();
}

Model::~Model()
{
    delete pSatelliteList;
    delete pStationList;
    delete pSettingsList;
}

QVector<Station*>* Model::stationList() const
{
    return pStationList;
}

QVector<Satellite*>* Model::satelliteList() const
{
    return pSatelliteList;
}

void Model::loadInitState ()
{
    QFile* pFile = new QFile("init.xml");
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
                pSatelliteList->append(new Satellite(attrs.value("name").toString(),attrs.value("maxBw").toInt(),
                                                 QPair<int,int>(attrs.value("posX").toInt(),attrs.value("posY").toInt())));
            if (xml.name() == "station")
                pStationList->append(new Station(attrs.value("name").toString(),pSatelliteList->last(),
                                                 QPair<int,int>(attrs.value("posX").toInt(),attrs.value("posY").toInt()),
                                                 attrs.value("call").toInt(),attrs.value("failure").toInt()));
            if (xml.name() == "settings")
                pSettingsList->append(QString(attrs.value("automatic_decisions").toString()));
        }
    }
    pFile->close();
    delete pFile;
}

void Model::processModelTact()
{
    tact++;
    if (tact % 30 == 0) phase0 ();
    phase1();
    phase2();
    phase3();
}

void Model::phase0()
{
    if (critHours)
    {
        critHours = false;
        for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
            (*it)->setStatus("Online");
    }
    else
    {
        critHours = true;
        for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
            (*it)->setStatus("Calling");
    }
}

void Model::phase1()
{
    int maximumBwPerStation = 512;
    int medianBwPerStation = 384;
    int minimalBwPerStation = 256;
    for (QVector<Satellite*>::iterator it = pSatelliteList->begin(); it != pSatelliteList->end(); it++)
    {
        if ((*it)->status() == "Offline") continue;
        //(*it)->setStatus("Online");
        if ((*it)->maxBw() >= ((*it)->stationCount()*maximumBwPerStation))
        {
            if (pSettingsList->at(0) == "true") emit showRecomendation("Switch " + (*it)->name() + " bw for each station to 512");
            (*it)->sharingBw = maximumBwPerStation;
            (*it)->setStationCount(0);
            continue;
        }
        if ((*it)->maxBw() >= ((*it)->stationCount()*medianBwPerStation))
        {
            if (pSettingsList->at(0) == "true") emit showRecomendation("Switch " + (*it)->name() + " bw for each station to 384");
            (*it)->sharingBw = 384;
            (*it)->setStationCount(0);
            continue;
        }
        if ((*it)->maxBw() >= ((*it)->stationCount()*minimalBwPerStation))
        {
            if (pSettingsList->at(0) == "true") emit showRecomendation("Switch " + (*it)->name() + " bw for each station to 256");
            (*it)->sharingBw = 256;
            (*it)->setStationCount(0);
            continue;
        }
        if ((*it)->maxBw() <= ((*it)->stationCount()*minimalBwPerStation))
        {
            if (pSettingsList->at(0) == "true") emit showRecomendation("Switch " + (*it)->name() + " bw for each station to 256");
            (*it)->setStatus("Overload");
            (*it)->sharingBw = 256;
            (*it)->setStationCount(0);
            continue;
        }
    }
}

void Model::phase2()
{
    for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
    {
        if ((*it)->groundConnectionAval() > 0) (*it)->decGroundConnectionAval();
                else (*it)->setBwInUse(0);
        if ((*it)->status() == "Online") (*it)->setBwNeeded(rand()%6 + 1);
        if ((*it)->status() == "Offline")
        {
            (*it)->setBwNeeded(0);
            return;
        }
        if ((*it)->status() == "Calling") (*it)->setBwNeeded(512);
        if ((*it)->status() == "StandBy") (*it)->setBwNeeded(512);
        if ((*it)->status() == "Connected") (*it)->setBwNeeded(512);
        (*it)->satellite()->setStationCount((*it)->satellite()->stationCount()+1);
        if (((*it)->groundConnectionAval() == 0) && ((*it)->failureChance() > rand()%100))
            (*it)->setGroundConnectionAval(rand()%4+3);
    }
}

void Model::phase3()
{
    for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
    {
        if ((*it)->status() == "Online")
        {
            if ((*it)->groundConnectionAval() != 0) (*it)->setBwInUse((*it)->bwNeeded());
        }
        if ((*it)->status() == "Offline") (*it)->setBwInUse(0);
        if ((*it)->status() == "Calling")
        {
            if ((*it)->satellite()->avalBw() > (*it)->satellite()->sharingBw)
            {
                (*it)->setStatus("Connected");
            }
            else
            {
                (*it)->setStatus("StandBy");
            }
        }
        if ((*it)->status() == "StandBy")
        {
            (*it)->setBwInUse(0);
            if ((*it)->satellite()->avalBw() > (*it)->satellite()->sharingBw)
            {
                (*it)->setStatus("Connected");
            }
        }
        if ((*it)->status() == "Connected")
        {
            (*it)->setBwNeeded(512);
            if ((*it)->groundConnectionAval() != 0) (*it)->setBwInUse((*it)->satellite()->sharingBw);
        }
    }
}
