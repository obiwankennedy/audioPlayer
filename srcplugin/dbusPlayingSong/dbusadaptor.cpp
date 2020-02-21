#include "dbusadaptor.h"

DbusAdaptor::DbusAdaptor(DbusPlugin* plugin, const SongFields* p) : QDBusAbstractAdaptor(plugin), m_p(p) {}
QString DbusAdaptor::title()
{
    return m_p->Title;
}
QString DbusAdaptor::artist()
{
    return m_p->Artist;
}
QString DbusAdaptor::album()
{
    return m_p->album;
}
void DbusAdaptor::setSong(const SongFields* p)
{
    m_p= p;
}
