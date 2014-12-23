#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <../../src/Model/satellite.h>
#include <../../src/Model/station.h>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class ConfigDialog : public QDialog
{
    Q_OBJECT

    public:
        ConfigDialog(QVector<Station*> *pStationList, QVector<Satellite*> *pSatelliteList, QWidget* parent = 0);

    public slots:
        void changePage(QListWidgetItem *current, QListWidgetItem *previous);

    private:
        void createIcons();

        QListWidget *pContentsWidget;
        QStackedWidget *pPagesWidget;
};

#endif
