#-------------------------------------------------
#
# Project created by QtCreator 2015-03-11T22:02:00
#
#-------------------------------------------------

QT       -= gui

TARGET = snmp_pp
TEMPLATE = lib

DEFINES += SNMP_PP_LIBRARY STDCXX_98_HEADERS HAVE_STRCASECMP

SOURCES += ../../src/snmp_pp/address.cpp \
    ../../src/snmp_pp/asn1.cpp \
    ../../src/snmp_pp/auth_priv.cpp \
    ../../src/snmp_pp/counter.cpp \
    ../../src/snmp_pp/ctr64.cpp \
    ../../src/snmp_pp/eventlist.cpp \
    ../../src/snmp_pp/eventlistholder.cpp \
    ../../src/snmp_pp/gauge.cpp \
    ../../src/snmp_pp/idea.cpp \
    ../../src/snmp_pp/integer.cpp \
    ../../src/snmp_pp/IPv6Utility.cpp \
    ../../src/snmp_pp/log.cpp \
    ../../src/snmp_pp/md5c.cpp \
    ../../src/snmp_pp/mp_v3.cpp \
    ../../src/snmp_pp/msec.cpp \
    ../../src/snmp_pp/msgqueue.cpp \
    ../../src/snmp_pp/notifyqueue.cpp \
    ../../src/snmp_pp/octet.cpp \
    ../../src/snmp_pp/oid.cpp \
    ../../src/snmp_pp/pdu.cpp \
    ../../src/snmp_pp/reentrant.cpp \
    ../../src/snmp_pp/sha.cpp \
    ../../src/snmp_pp/snmpmsg.cpp \
    ../../src/snmp_pp/target.cpp \
    ../../src/snmp_pp/timetick.cpp \
    ../../src/snmp_pp/usm_v3.cpp \
    ../../src/snmp_pp/uxsnmp.cpp \
    ../../src/snmp_pp/v3.cpp \
    ../../src/snmp_pp/vb.cpp

HEADERS += ../../src/snmp_pp/snmp_pp/address.h \
    ../../src/snmp_pp/snmp_pp/asn1.h \
    ../../src/snmp_pp/snmp_pp/auth_priv.h \
    ../../src/snmp_pp/snmp_pp/collect.h \
    ../../src/snmp_pp/snmp_pp/config_snmp_pp.h \
    ../../src/snmp_pp/snmp_pp/counter.h \
    ../../src/snmp_pp/snmp_pp/ctr64.h \
    ../../src/snmp_pp/snmp_pp/eventlist.h \
    ../../src/snmp_pp/snmp_pp/eventlistholder.h \
    ../../src/snmp_pp/snmp_pp/gauge.h \
    ../../src/snmp_pp/snmp_pp/idea.h \
    ../../src/snmp_pp/snmp_pp/integer.h \
    ../../src/snmp_pp/snmp_pp/IPv6Utility.h \
    ../../src/snmp_pp/snmp_pp/log.h \
    ../../src/snmp_pp/snmp_pp/md5.h \
    ../../src/snmp_pp/snmp_pp/mp_v3.h \
    ../../src/snmp_pp/snmp_pp/msec.h \
    ../../src/snmp_pp/snmp_pp/msgqueue.h \
    ../../src/snmp_pp/snmp_pp/notifyqueue.h \
    ../../src/snmp_pp/snmp_pp/octet.h \
    ../../src/snmp_pp/snmp_pp/oid.h \
    ../../src/snmp_pp/snmp_pp/oid_def.h \
    ../../src/snmp_pp/snmp_pp/pdu.h \
    ../../src/snmp_pp/snmp_pp/reentrant.h \
    ../../src/snmp_pp/snmp_pp/sha.h \
    ../../src/snmp_pp/snmp_pp/smi.h \
    ../../src/snmp_pp/snmp_pp/smival.h \
    ../../src/snmp_pp/snmp_pp/snmperrs.h \
    ../../src/snmp_pp/snmp_pp/snmpmsg.h \
    ../../src/snmp_pp/snmp_pp/target.h \
    ../../src/snmp_pp/snmp_pp/timetick.h \
    ../../src/snmp_pp/snmp_pp/usm_v3.h \
    ../../src/snmp_pp/snmp_pp/uxsnmp.h \
    ../../src/snmp_pp/snmp_pp/v3.h \
    ../../src/snmp_pp/snmp_pp/vb.h \
    ../../src/snmp_pp/libsnmp.h \
    ../../src/snmp_pp/snmp_pp.h

win32: DEPENDPATH += $$PWD/../../src/openssl
win32: INCLUDEPATH += $$PWD/../../src/openssl/include
win32: LIBS += -L$$PWD/../../src/openssl -lssl -lcrypto -lws2_32
