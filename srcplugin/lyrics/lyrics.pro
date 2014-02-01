TEMPLATE = lib \
    plugin
CONFIG += plugin
QT += xml \
    network
QT += multimedia printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../src/plugins/plugins.pri)
INCLUDEPATH += ../../src \
    ../../src/decorator \
    ../../src/tagger \
    ../../src/plugins \
    /usr/include/taglib/
HEADERS = lyricsplugin.h \
    lyricsviewerdock.h \
    lyricsfinder.h \
    AbstractLyricsFinder.h \
    wikiflyfinder.h \
    wikifinder.h
SOURCES = lyricsplugin.cpp \
    lyricsviewerdock.cpp \
    lyricsfinder.cpp \
    wikiflyfinder.cpp \
    wikifinder.cpp


TARGET = $$qtLibraryTarget(lyrics)
DESTDIR = ../../bin/plugins
FORMS += lyricsviewer.ui

OTHER_FILES += \
    lyrics.json
