TEMPLATE = lib \
    plugin
CONFIG += plugin debug
QT += network
include(../../src/plugins/plugins.pri)

INCLUDEPATH += /usr/include/gstreamer-0.10/ \
    /usr/include/glib-2.0 \
    /usr/include/glib-2.0 \
    /usr/include/libxml2/ \
    /usr/lib/glib-2.0/include/
LIBS += -lgstreamer-0.10 -lglib-2.0
INCLUDEPATH += ../../src \
    ../../src/decorator \
    ../../src/tagger \
    ../../src/plugins \
    /usr/include/taglib/
HEADERS = musicbrainplugin.h \
    fingerprinter.h \
    musicdnsclient.h \
    musicbrainzclient.h

SOURCES = musicbrainplugin.cpp \
    fingerprinter.cpp \
    musicdnsclient.cpp \
    musicbrainzclient.cpp

TARGET = $$qtLibraryTarget(musicbrain)
DESTDIR = ../../bin/plugins
