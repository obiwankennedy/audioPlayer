/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c DbusAdaptor -p adaptor.h:adaptor.cpp eu.renaudguezennec.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef ADAPTOR_H_1357939089
#define ADAPTOR_H_1357939089

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface local.Player
 */
class DbusAdaptor: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "local.Player"; }

public:
    DbusAdaptor(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~DbusAdaptor();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> decreaseSong()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("decreaseSong"), argumentList);
    }

    inline QDBusPendingReply<> decreaseSong(int i)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(i);
        return asyncCallWithArgumentList(QLatin1String("decreaseSong"), argumentList);
    }

    inline QDBusPendingReply<> increaseSong()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("increaseSong"), argumentList);
    }

    inline QDBusPendingReply<> increaseSong(int i)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(i);
        return asyncCallWithArgumentList(QLatin1String("increaseSong"), argumentList);
    }

    inline QDBusPendingReply<> nextSong()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("nextSong"), argumentList);
    }

    inline QDBusPendingReply<> pauseSong()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("pauseSong"), argumentList);
    }

    inline QDBusPendingReply<> playSong()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("playSong"), argumentList);
    }

    inline QDBusPendingReply<> previousSong()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("previousSong"), argumentList);
    }

    inline QDBusPendingReply<> seek(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("seek"), argumentList);
    }

    inline QDBusPendingReply<> setSelectionMode(int mode)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(mode);
        return asyncCallWithArgumentList(QLatin1String("setSelectionMode"), argumentList);
    }

    inline QDBusPendingReply<> setVolume(int in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("setVolume"), argumentList);
    }

    inline QDBusPendingReply<> stopSong()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("stopSong"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void SetId(int i);
    void playingStop();
};

namespace local {
  typedef ::DbusAdaptor Player;
}
#endif
