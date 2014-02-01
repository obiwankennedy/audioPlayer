TEMPLATE = app
LANGUAGE = C++
CONFIG += qt \
    thread \
    assistant \
    warn_on

include(factory/factory.pri)
include(document/document.pri)
include(directoryFacade/directoryFacade.pri)
include(command/command.pri)
include(decorator/decorator.pri)
include(deleguate/deleguate.pri)
include(tagger/tagger.pri)
include(preferences/preferences.pri)
include(plugins/plugins.pri)
include(regexwizzard/regexwizzard.pri)
include(tabapi/tabapi.pri)
include(listview/listview.pri)
#include(Style/Style.pri)


DEPENDPATH += directoryFacade \
    factory \
    tageditor \
    translations \
    document \
    command \
    deleguate \
    pixmaps \
    decorator \
    tagger \
    listview \
    preferences \
    regexwizzard \
    tabapi \
    ../bin \
    plugins


INCLUDEPATH += . \
    factory \
    Style \
    directoryFacade \
    pixmaps \
    wizzardexport \
    document \
    command \
    decorator \
    deleguate \
    preferences \
    listview \
    tagger \
    plugins \
    regexwizzard \
    tabapi \
    src \
    /usr/local/include/taglib/

HEADERS += edittagbox.h \
    mediatype.h \
    pl_tableview.h \
    playlist.h \
    playlistgenerator.h \
    playlistitem.h \
    playlistmodel.h \
    playlistviewer.h \
    data.h \
    amendtag.h \
    visitormedia.h \
    thread.h \
    visitormediaseeker.h \
    wizzardexport.h \
    pl_defaultaudio.h \
    pl_itemcompare.h \
    sortdialog.h \
    importparser.h \
    plsimport.h \
    xmlimport.h \
    player.h \
    pl_treeview.h \
    pl_treemodel.h \
    pl_treeitem.h \
    pl_texteditordelegate.h \
    search_dialogimpl.h \
    searchmodel.h \
    searchdialogitem.h \
    tableheaderview.h \
    pl_databasemanager.h \
    dbus/dbusServer.h

FORMS += tageditor/tageditordialog.ui \
    wizzardexport/wizzardexport.ui \
    sortui/sortui.ui \
    preferences/preferences.ui \
    findingassistant/findingassistant.ui


SOURCES += edittagbox.cpp \
    main.cpp \
    pl_tableview.cpp \
    playlist.cpp \
    playlistgenerator.cpp \
    playlistitem.cpp \
    playlistmodel.cpp \
    playlistviewer.cpp \
    amendtag.cpp \
    visitormedia.cpp \
    thread.cpp \
    visitormediaseeker.cpp \
    wizzardexport.cpp \
    pl_defaultaudio.cpp \
    pl_itemcompare.cpp \
    sortdialog.cpp \
    importparser.cpp \
    plsimport.cpp \
    xmlimport.cpp \
    player.cpp \
    pl_treeview.cpp \
    pl_treemodel.cpp \
    pl_treeitem.cpp \
    pl_texteditordelegate.cpp \
    search_dialogimpl.cpp \
    searchmodel.cpp \
    searchdialogitem.cpp \
    tableheaderview.cpp \
    pl_databasemanager.cpp \
    dbus/dbusServer.cpp



#DEFINES += REPEAT

LIBS += -lid3 \
    -L/usr/local/lib -ltag

QT += xml \
    core \
    dbus \
    sql \
    svg \
    gui

QT += multimedia printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#lessThan(QT_MAJOR_VERSION, 5): QT += phonon


documentation.path = /usr/local/audioPlayer/documentation/
documentation.files = ../documentation/*
target.path = /usr/local/bin
INSTALLS += documentation \
    target
VERSION = 0.9.1
TARGET = ../bin/audioPlayer
TRANSLATIONS = ../resources/translation/audioPlayer_fr_FR.ts
UI_DIR = ../ui
MOC_DIR = ../obj
OBJECTS_DIR = ../obj

QMAKE_CXXFLAGS=-fstack-protector -W -Wall -Wextra -pedantic -Wstack-protector -Wno-long-long -Wno-overlength-strings
