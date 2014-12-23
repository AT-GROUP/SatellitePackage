#ifndef REALGRAPHDIALOG_H
#define REALGRAPHDIALOG_H

#include <QDialog>
#include "../SNMP/RealWorld.h"
#include "RealGraphicsWidget.h"
#include "RealStationDataTable.h"

class RealGraphDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RealGraphDialog(RealWorld* mod, RealStatisticCollector* sc, QWidget *parent = 0);

signals:

public slots:

};

#endif // REALGRAPHDIALOG_H
