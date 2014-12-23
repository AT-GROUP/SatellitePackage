#ifndef ROUTERPOOL_H
#define ROUTERPOOL_H

#include <QMap>
#include "SnmpRouter.h"
#include <QObject>
#include <QTimer>

class RouterPool
{
private:
    QMap<QString, SnmpRouter*> routers;
    int interval;
public:
    RouterPool();
    void setInterval(int interval);
    int getInterval();
    void addRouter(QString ip);
    SnmpRouter* getRouter(QString ip);
    void updateRouters();
};

#endif // ROUTERPOOL_H
