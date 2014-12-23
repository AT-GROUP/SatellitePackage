#ifndef QSATELLITEITEM_H
#define QSATELLITEITEM_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTableView>
#include "../../src/Model/satellite.h"

class QSatelliteItem: public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
    private:
        QGraphicsPixmapItem *icon;
		QGraphicsProxyWidget *proxy;
        QTableView *pInfoList;
        Satellite *pSatellite;
    public:
        QSatelliteItem(Satellite *satellite, QObject* parent = 0);
        ~QSatelliteItem();
		void updateFact(std::tuple<QString, QString, QString> info);
        Satellite * satellite() const;
	protected:
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	signals:
        void valueChanged(const QString& mess);
    public slots:
        void updateFact(const StrPair &info);
};

#endif // QSATELLITEITEM_H
