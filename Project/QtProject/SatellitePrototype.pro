TEMPLATE = subdirs

win32: SUBDIRS += \
    Wrapper \
    Model \
    snmp_pp \
    SNMP \
    Visualizer \
    Prototype

unix: SUBDIRS += \
    Wrapper \
    Model \
    SNMP \
    Visualizer \
    Prototype

