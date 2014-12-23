#ifndef REALSATELLITE_H
#define REALSATELLITE_H

#include <QString>

class RealSatellite
{
private:
    QString _name;
    int _maxInBw;
    int _maxOutBw;

    int _curInBw;
    int _curOutBw;
public:
    RealSatellite(QString name, int maxInBw, int maxOutBw);
    int curInBw();
    int curOutBw();
    int maxInBw();
    int maxOutBw();
    int maxBw();
    int curBw();
    QString name();

    void setCurInBw(int val);
    void setCurOutBw(int val);
    void incCurInBw(int val);
    void incCurOutBw(int val);
};

#endif // REALSATELLITE_H
