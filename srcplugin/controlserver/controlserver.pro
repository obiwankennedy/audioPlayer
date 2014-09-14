TEMPLATE = lib \
    plugin
CONFIG += plugin debug
QT += network dbus
QT +=  printsupport

#multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../src/plugins/plugins.pri)

#INCLUDEPATH += /usr/include/gstreamer-0.10/ \
#    /usr/include/glib-2.0 \
 #   /usr/include/glib-2.0 \
 #   /usr/include/libxml2/ \
 #   /usr/lib/glib-2.0/include/
#LIBS += -lgstreamer-0.10 -lglib-2.0
INCLUDEPATH += ../../src \
    ../../src/decorator \
    ../../src/tagger \
    ../../src/plugins \
    /usr/include/taglib/
HEADERS =  \
    controlserverplugin.h \
    serverthread.h \
    servertext.h \
    adaptor.h

SOURCES =  \
    controlserverplugin.cpp \
    serverthread.cpp \
    servertext.cpp \
    adaptor.cpp

TARGET = $$qtLibraryTarget(ControlServer)
DESTDIR = ../../bin/plugins

OTHER_FILES += \
    servercontrol.json
