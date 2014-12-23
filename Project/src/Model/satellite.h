#ifndef SATELLITE_H
#define SATELLITE_H

#include <QObject>
#include <QPointF>
#include <QPair>

typedef QPair<QString,QString> StrPair;

class Satellite : public QObject
{
    Q_OBJECT
    public:
        Satellite(QString name, int maxBw, QPair<int,int> pos,
                  QString ipAddress = "192.168.1.1", int curBw = 0, int stationCount = 0,
                  QString status = "Online", QObject* parent = 0);

        int sharingBw;
        QString name() const;
        QString ipAddress() const;
        int maxBw() const;
        int curBw() const;
        int avalBw() const;
        int stationCount() const;
        QString status() const;
        QPointF* pos() const;

        void setName(QString newName);
        void setIpAddress(QString newIpAddress);
        void setMaxBw(int newMaxBw);
        void setCurBw(int newCurBw);
        void setStationCount(int newStationCount);
        void setStatus(QString newStatus);
        void refreshData();

    private:
        QString name_;
        QString ipAddress_;
        int maxBw_;
        int curBw_;
        int stationCount_;
        QString status_;
        QPointF *pos_;

    signals:
        void attrChanged(const StrPair& info);
};

#endif // SATELLITE_H
