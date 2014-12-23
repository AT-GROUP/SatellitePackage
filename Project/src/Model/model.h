#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include "satellite.h"
#include "station.h"
#include <QTime>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT
    public:
        Model(QObject *parent = 0);
        ~Model();
        QVector<Station*>* stationList() const;
        QVector<Satellite*>* satelliteList() const;
        void processModelTact();
    private:
        QVector<Station*> *pStationList;
        QVector<Satellite*> *pSatelliteList;
        QVector<QString> *pSettingsList;
        int tact;
        bool critHours;
        void loadInitState();

        void phase0();
        void phase1();
        void phase2();
        void phase3();
    signals:
        void showRecomendation(const QString& recomendation);
};

#endif // MODEL_H
