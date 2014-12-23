#ifndef QSTATIONITEM_H
#define QSTATIONITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTableWidget>
#include "../../src/Model/station.h"

class QStationItem: public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
    private:
        QGraphicsEllipseItem *pEllipse;
		QGraphicsProxyWidget *proxy;
        QTableView *pInfoList;
        Station *pStation;
		void updateColor();
		void setColor(QColor qColor);
    public:
        QStationItem(Station* station, QObject* parent = 0);
        ~QStationItem();
        Station * station() const;
    protected:
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	signals:
		void valueChanged(const QString& mess);
    public slots:
        void updateFact(const StrPair &info);
};

#endif // QSTATIONITEM_H
