TEMPLATE = lib \
    plugin
CONFIG += plugin debug
QT += dbus

QT += multimedia printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


include(../../src/plugins/plugins.pri)
INCLUDEPATH += ../../src \
    ../../src/decorator \
    ../../src/tagger \
    ../../src/plugins \
    /usr/include/taglib/
HEADERS = dbusplugin.h #\
    #dbusadaptor.h
SOURCES = dbusplugin.cpp #\
    #dbusadaptor.cpp
TARGET = $$qtLibraryTarget(dbusPlayingSong)
DESTDIR = ../../bin/plugins

OTHER_FILES += \
    dbus.json
