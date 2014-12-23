TEMPLATE = lib
CONFIG += console qt
CONFIG -= app_bundle

HEADERS += \
    ../../src/Model/model.h \
    ../../src/Model/satellite.h \
    ../../src/Model/station.h

SOURCES += \
    ../../src/Model/model.cpp \
    ../../src/Model/satellite.cpp \
    ../../src/Model/station.cpp

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    ../../Build/QtCreator/Prototype/init.xml
