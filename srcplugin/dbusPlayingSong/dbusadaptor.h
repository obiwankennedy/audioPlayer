#ifndef DBUSADAPTOR_H
#define DBUSADAPTOR_H
#include <QDBusAbstractAdaptor>
#include <songplugin.h>
#include "dbusplugin.h"

class DbusAdaptor : public QDBusAbstractAdaptor
{
    Q_CLASSINFO("D-Bus Interface", "org.playlistgenerator.DBus.DbusPlugin")
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString artist READ artist)
    Q_PROPERTY(QString album READ album)

     const SongFields* m_p;
public:
    DbusAdaptor(DbusPlugin* plugin,const SongFields* p);

    QString title();
    QString artist();
    QString album();
    void setSong(const SongFields* p);
};

#endif // DBUSADAPTOR_H
