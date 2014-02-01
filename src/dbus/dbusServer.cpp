/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c DbusAdaptorServer -a dbusServer.h:dbusServer.cpp eu.renaudguezennec.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "dbusServer.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class DbusAdaptorServer
 */

DbusAdaptorServer::DbusAdaptorServer(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

DbusAdaptorServer::~DbusAdaptorServer()
{
    // destructor
}

void DbusAdaptorServer::decreaseSong()
{
    // handle method call local.Player.decreaseSong
    QMetaObject::invokeMethod(parent(), "decreaseSong");
}

void DbusAdaptorServer::decreaseSong(int i)
{
    // handle method call local.Player.decreaseSong
    QMetaObject::invokeMethod(parent(), "decreaseSong", Q_ARG(int, i));
}

void DbusAdaptorServer::increaseSong()
{
    // handle method call local.Player.increaseSong
    QMetaObject::invokeMethod(parent(), "increaseSong");
}

void DbusAdaptorServer::increaseSong(int i)
{
    // handle method call local.Player.increaseSong
    QMetaObject::invokeMethod(parent(), "increaseSong", Q_ARG(int, i));
}

void DbusAdaptorServer::nextSong()
{
    // handle method call local.Player.nextSong
    QMetaObject::invokeMethod(parent(), "nextSong");
}

void DbusAdaptorServer::pauseSong()
{
    // handle method call local.Player.pauseSong
    QMetaObject::invokeMethod(parent(), "pauseSong");
}

void DbusAdaptorServer::playSong()
{
    // handle method call local.Player.playSong
    QMetaObject::invokeMethod(parent(), "playSong");
}

void DbusAdaptorServer::previousSong()
{
    // handle method call local.Player.previousSong
    QMetaObject::invokeMethod(parent(), "previousSong");
}

void DbusAdaptorServer::seek(const QString &in0)
{
    // handle method call local.Player.seek
    QMetaObject::invokeMethod(parent(), "seek", Q_ARG(QString, in0));
}

void DbusAdaptorServer::setSelectionMode(int mode)
{
    // handle method call local.Player.setSelectionMode
    QMetaObject::invokeMethod(parent(), "setSelectionMode", Q_ARG(int, mode));
}

void DbusAdaptorServer::setVolume(int in0)
{
    // handle method call local.Player.setVolume
    QMetaObject::invokeMethod(parent(), "setVolume", Q_ARG(int, in0));
}

void DbusAdaptorServer::stopSong()
{
    // handle method call local.Player.stopSong
    QMetaObject::invokeMethod(parent(), "stopSong");
}
