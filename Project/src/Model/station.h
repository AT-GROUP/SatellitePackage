#ifndef STATION_H
#define STATION_H

#include <QObject>
#include "satellite.h"
#include <QPointF>

class Station : public QObject
{
    Q_OBJECT
    public:
        Station(QString name, Satellite *satellite, QPair<int,int> pos, int callChance = 3, int failureChance = 2,
                QString ipAddress = "192.168.1.1", int bwNeeded = 0, int bwInUse = 0,
                QString status = "Online", QObject* parent = 0);

        QString name() const;
        QString ipAddress() const;
        int bwNeeded() const;
        int bwInUse() const;
        Satellite* satellite() const;
        QString status() const;
        QPointF* pos() const;
        int callChance() const;
        int failureChance() const;
        int groundConnectionAval() const;
        void setName(QString newName);
        void setBwNeeded(int newBwNeeded);
        void setBwInUse(int newBwInUse);
        void setIpAddress(QString newIpAddress);
        void setSatellite(Satellite *newSatellite);
        void setStatus(QString newStatus);
        void refreshData();
        void setGroundConnectionAval(int groundConnection);
        void decGroundConnectionAval();

    private:
        QString name_;
        QString status_;
        int bwNeeded_;
        int bwInUse_;
        QString ipAddress_;
        Satellite *satellite_;
        QPointF *pos_;
        int callChance_;
        int failureChance_;
        int groundConnection_;
    signals:
        void attrChanged(const StrPair& info);
};

#endif // STATION_H
