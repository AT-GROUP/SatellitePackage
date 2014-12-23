#include "RealSatellite.h"
#include <cmath>

RealSatellite::RealSatellite(QString name, int maxInBw, int maxOutBw) : _name(name), _maxInBw(maxInBw), _maxOutBw(maxOutBw), _curInBw(0), _curOutBw(0)
{}

QString RealSatellite::name()
{
    return _name;
}

int RealSatellite::curInBw()
{
    return _curInBw;
}

int RealSatellite::curOutBw()
{
    return _curOutBw;
}

int RealSatellite::curBw()
{
    return std::max(_curInBw, _curOutBw);
}

int RealSatellite::maxInBw()
{
    return _maxInBw;
}

int RealSatellite::maxOutBw()
{
    return _maxOutBw;
}

int RealSatellite::maxBw()
{
    return std::max(_maxInBw, _maxOutBw);
}

void RealSatellite::setCurInBw(int val)
{
    _curInBw = val;
}

void RealSatellite::setCurOutBw(int val)
{
    _curOutBw = val;
}

void RealSatellite::incCurInBw(int val)
{
    _curInBw += val;
}

void RealSatellite::incCurOutBw(int val)
{
    _curOutBw += val;
}

