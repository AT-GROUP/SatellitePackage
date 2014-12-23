QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Visualizer
TEMPLATE = lib

SOURCES += \
    ../../src/Visualizer/ConfigDialog.cpp \
    ../../src/Visualizer/ConfigPages.cpp \
    ../../src/Visualizer/InfoTableModel.cpp \
    ../../src/Visualizer/ModelVisualizer.cpp \
    ../../src/Visualizer/QSatelliteItem.cpp \
    ../../src/Visualizer/QStationItem.cpp \
    ../../src/Visualizer/StatisticCollector.cpp \
    ../../src/Visualizer/qcustomplot.cpp \
    ../../src/Visualizer/GraphicsWidget.cpp \
    ../../src/Visualizer/GraphDialog.cpp \
    ../../src/Visualizer/StationDataTable.cpp \
    ../../src/Visualizer/RealGraphDialog.cpp \
    ../../src/Visualizer/RealStationDataTable.cpp \
    ../../src/Visualizer/RealGraphicsWidget.cpp \
    ../../src/Visualizer/MessageList.cpp
HEADERS  += \
    ../../src/Visualizer/ConfigDialog.h \
    ../../src/Visualizer/ConfigPages.h \
    ../../src/Visualizer/InfoTableModel.h \
    ../../src/Visualizer/ModelVisualizer.h \
    ../../src/Visualizer/QSatelliteItem.h \
    ../../src/Visualizer/QStationItem.h \
    ../../src/Visualizer/StatisticCollector.h \
    ../../src/Visualizer/qcustomplot.h \
    ../../src/Visualizer/GraphicsWidget.h \
    ../../src/Visualizer/GraphDialog.h \
    ../../src/Visualizer/StationDataTable.h \
    ../../src/Visualizer/RealGraphDialog.h \
    ../../src/Visualizer/RealStationDataTable.h \
    ../../src/Visualizer/RealGraphicsWidget.h \
    ../../src/Visualizer/MessageList.h

RESOURCES += \
    ../../src/Visualizer/Resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Model/release/ -lModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Model/debug/ -lModel
else:unix: LIBS += -L$$OUT_PWD/../Model/ -lModel

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SNMP/release/ -lSNMP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SNMP/debug/ -lSNMP
else:unix: LIBS += -L$$OUT_PWD/../SNMP/ -lSNMP

INCLUDEPATH += $$PWD/../Model
INCLUDEPATH += $$PWD/../SNMP

DEPENDPATH += $$PWD/../Model
DEPENDPATH += $$PWD/../SNMP

QMAKE_CXXFLAGS += -std=c++11
