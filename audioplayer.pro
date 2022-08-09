TEMPLATE = app

PROJECT = audioplayer

LANGUAGE = C++
QT += gui core quick quickwidgets dbus svg xml multimedia printsupport quickcontrols2

SOURCES += main.cpp maincontroller.cpp \
    albumpictureprovider.cpp \
    audiocontroller.cpp \
    audiofilemodel.cpp worker/theme.cpp \
    commandserver.cpp \
    filteredmodel.cpp \
    worker/filereaderhelper.cpp


HEADERS += maincontroller.h \
    albumpictureprovider.h \
    audiocontroller.h \
    audiofilemodel.h worker/theme.h \
    commandserver.h \
    filteredmodel.h \
    worker/filereaderhelper.h

OTHER_FILES += *.qml resources/qml/*.qml

LIBS += -ltag

VERSION = 1.0.0
TARGET = audioPlayer
TRANSLATIONS = resources/translation/audioPlayer_fr_FR.ts
UI_DIR = ui
MOC_DIR = obj
OBJECTS_DIR = obj

CONFIG += c++11


QMAKE_CXXFLAGS=-fstack-protector -W -Wall -Wextra -pedantic -Wstack-protector -Wno-long-long -Wno-overlength-strings

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources/qml/AudioPlayer.qml \
    resources/qml/EditMenu.qml \
    resources/qml/ImageButton.qml
