#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDebug>
#include <QtGui>
#include <QtWidgets>

#include "dbusplugin.h"
bool DbusPlugin::hasUI()
{
    return false;
}

void DbusPlugin::SetSong(SongFields* p)
{
    if(!m_action->isChecked())
    {
        stopped();
        return;
    }

    m_p= p;

    QDBusConnection sessionbus= QDBusConnection::sessionBus();

    if(!sessionbus.isConnected())
    {
        fprintf(stderr, "Could not connect to session bus\n");
    }

    // QDBusMessage m =
    // QDBusMessage::createMethodCall("im.pidgin.purple.PurpleService","/im/pidgin/purple/PurpleObject","im.pidgin.purple.PurpleInterface","PurpleUtilSetCurrentSong");

    /* QList<QVariant> args;
     args << m_p->Title << m_p->Artist << m_p->album;
     m.setArguments(args);
     QDBusMessage metadatamsg = sessionbus.call(m);*/

    /* if(metadatamsg.type() != QDBusMessage::ReplyMessage)
         qDebug() << "Error its not a message " << metadatamsg.type() <<metadatamsg.errorMessage ();*/
}
void DbusPlugin::stopped()
{
    /*   QDBusConnection sessionbus = QDBusConnection::sessionBus();

          if ( !sessionbus.isConnected() )
           {
               fprintf(stderr,"Could not connect to session bus\n");

           }
       QDBusMessage m =
       QDBusMessage::createMethodCall("im.pidgin.purple.PurpleService","/im/pidgin/purple/PurpleObject","im.pidgin.purple.PurpleInterface","PurpleUtilSetCurrentSong");

       QList<QVariant> args;
       args << "" << "" << "";
       m.setArguments(args);
       QDBusMessage metadatamsg = sessionbus.call(m);

       if(metadatamsg.type() != QDBusMessage::ReplyMessage)
           qDebug() << "Error its not a message " << metadatamsg.type() <<metadatamsg.errorMessage ();*/
}

QString DbusPlugin::getName()
{
    m_action= new QAction("Pidgin's Current Song", this);
    m_action->setCheckable(true);
    m_action->setChecked(true);
    m_action->setShortcut(tr("Ctrl+B"));
    m_action->setStatusTip(tr("Send informations about the played song to Pidgin"));
    // connect(m_action, SIGNAL(triggered()), this, SLOT(toggle()));

    return tr("Dbus");
}

QAction* DbusPlugin::getAction()
{
    return m_action;
}

QDockWidget* DbusPlugin::getWidget()
{
    return NULL;
}
bool DbusPlugin::isVisible()
{
    return false;
}

Qt::DockWidgetArea DbusPlugin::orientation()
{
    return Qt::BottomDockWidgetArea;
}

void DbusPlugin::readSetting(QSettings& settings)
{
    return;
}

void DbusPlugin::writeSetting(QSettings& settings)
{
    return;
}
void DbusPlugin::show()
{
    return;
}

void DbusPlugin::refresh()
{
    return;
}

// Q_EXPORT_PLUGIN2(dbusPlayingSong, DbusPlugin);
