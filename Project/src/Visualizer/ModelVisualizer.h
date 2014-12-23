#ifndef MODELVISUALIZER_H
#define MODELVISUALIZER_H

#include "QSatelliteItem.h"
#include "QStationItem.h"
#include "StatisticCollector.h"
#include "GraphicsWidget.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QListWidget>
#include <QXmlStreamReader>
#include <qmenubar.h>
#include "../../src/Model/model.h"
#include "../SNMP/RealWorld.h"
#include "../SNMP/RealStatisticCollector.h"
#include "RealGraphDialog.h"
#include "MessageList.h"

class ModelVisualizer : public QWidget
{
    Q_OBJECT
	private:
        QGraphicsScene *pScene;
        QGraphicsView *pView;
        QGraphicsPixmapItem *pBackGroundPic;
        QGridLayout *pGridLayout;
        MessageList* messages;
        QListView *pEventList;
        QMenuBar *pMainMenu;
        Model *pModel;
        RealWorld *pWorld;
        StatisticCollector* statistics;
        RealStatisticCollector* realStatistics;
	public:
		explicit ModelVisualizer(QWidget *parent = 0);
		~ModelVisualizer();
        QAction *startSim;
        QAction *pauseSim;
        QAction *configure;
        QAction *showInfo;
        QAction *action5;
        QAction *action6;
        QAction *showRealGraph;
        void processModelTact();
	public slots:
		void addMessageToEventsList(const QString& message);
		void showGraphsWindow();
        void showRealGraphsWindow();
        void showConfigWindow();
        void showMessageWindow(const QString &recomendation);
	protected:
		virtual void wheelEvent(QWheelEvent* event);
	private:
		void mapZoom(qreal factor, QPointF centerPoint);
		void createMenu();
		void createView();
		void createWidgets();
		void createLayout();
        void addStations();
        void initStatistics();
	signals:
		void pause();
};

#endif // MODELVISUALIZER_H
