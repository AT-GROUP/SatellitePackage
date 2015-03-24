#-------------------------------------------------
#
# Project created by QtCreator 2014-11-28T19:55:40
#
#-------------------------------------------------

QT       -= gui
QT       += concurrent

TARGET = SNMP
TEMPLATE = lib

DEFINES += SNMP_LIBRARY

SOURCES += \
    ../../src/SNMP/RouterPool.cpp \
    ../../src/SNMP/SnmpRouter.cpp \
    ../../src/SNMP/RealWorld.cpp \
    ../../src/SNMP/RealStation.cpp \
    ../../src/SNMP/RealSatellite.cpp \
    ../../src/SNMP/RealStatisticCollector.cpp

HEADERS += \
    ../../src/SNMP/RouterPool.h \
    ../../src/SNMP/SnmpRouter.h \
    ../../src/SNMP/RealWorld.h \
    ../../src/SNMP/RealStation.h \
    ../../src/SNMP/RealSatellite.h \
    ../../src/SNMP/RealStatisticCollector.h

QMAKE_CXXFLAGS += -std=c++11

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../snmp_pp/release/ -lsnmp_pp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../snmp_pp/debug/ -lsnmp_pp

INCLUDEPATH += $$PWD/../snmp_pp
DEPENDPATH += $$PWD/../snmp_pp
