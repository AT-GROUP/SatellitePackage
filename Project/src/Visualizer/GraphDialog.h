#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include "GraphicsWidget.h"
#include "StationDataTable.h"

class GraphDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GraphDialog(Model* mod, StatisticCollector* sc, QWidget *parent = 0);

signals:

public slots:

};

#endif // GRAPHDIALOG_H
