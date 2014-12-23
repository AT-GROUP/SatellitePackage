QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Prototype
TEMPLATE = app


SOURCES += \
    ../../src/Prototype/ATDynamicIESApp.cpp \
    ../../src/Prototype/main.cpp

HEADERS  += \
    ../../src/Prototype/ATDynamicIESApp.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Model/release/ -lModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Model/debug/ -lModel
else:unix: LIBS += -L$$OUT_PWD/../Model/ -lModel

INCLUDEPATH += $$PWD/../Model
DEPENDPATH += $$PWD/../Model

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Visualizer/release/ -lVisualizer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Visualizer/debug/ -lVisualizer
else:unix: LIBS += -L$$OUT_PWD/../Visualizer/ -lVisualizer

INCLUDEPATH += $$PWD/../Visualizer
DEPENDPATH += $$PWD/../Visualizer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Wrapper/release/ -lWrapper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Wrapper/debug/ -lWrapper
else:unix: LIBS += -L$$OUT_PWD/../Wrapper/ -lWrapper

INCLUDEPATH += $$PWD/../Wrapper
DEPENDPATH += $$PWD/../Wrapper

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SNMP/release/ -lSNMP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SNMP/debug/ -lSNMP
else:unix: LIBS += -L$$OUT_PWD/../SNMP/ -lSNMP

INCLUDEPATH += $$PWD/../SNMP
DEPENDPATH += $$PWD/../SNMP

QMAKE_CXXFLAGS += -std=c++11

