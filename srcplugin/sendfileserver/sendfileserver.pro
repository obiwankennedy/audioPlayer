TEMPLATE = lib \
    plugin
CONFIG += plugin debug
QT += network dbus
QT +=  printsupport

#multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../src/plugins/plugins.pri)


INCLUDEPATH += ../../src \
    ../../src/decorator \
    ../../src/tagger \
    ../../src/plugins \
    /usr/include/taglib/
HEADERS =  \
    serverthread.h \
    sendserverplugin.h \
    sendingserver.h \
    sendfileadaptor.h

SOURCES =  \
    serverthread.cpp \
    sendserverplugin.cpp \
    sendingserver.cpp \
    sendfileadaptor.cpp

TARGET = $$qtLibraryTarget(SendServerPlugin)
DESTDIR = ../../bin/plugins

OTHER_FILES +=

DISTFILES += \
    SendServerPlugin.json
