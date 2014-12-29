#include "sendserverplugin.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QtGui>
#include <QDBusMessage>
#include <QtWidgets>
#include <QDebug>


bool ControlServerPlugin::hasUI()
{
    return false;
}

void ControlServerPlugin::SetSong(SongFields* p)
{
    return;
}
void ControlServerPlugin::stopped()
{
    
}

QString ControlServerPlugin::getName()
{

    m_action = new QAction(tr("Remote Control Server"),this);
    m_external = new ServerThread;
    m_action->setCheckable(true);
    m_action->setChecked(true);
    m_action->setShortcut(tr("Ctrl+R"));
    m_action->setStatusTip(tr("Allow the application to be controlled by external system"));
    //connect(m_action, SIGNAL(triggered()), this, SLOT(toggle()));
    m_external->start();
    return tr("Remote");
}

QAction* ControlServerPlugin::getAction()
{
    return m_action;
}

QDockWidget* ControlServerPlugin::getWidget()
{
    return NULL;
}
bool ControlServerPlugin::isVisible()
{
    return false;
}

Qt::DockWidgetArea ControlServerPlugin::orientation()
{
    return Qt::BottomDockWidgetArea;
}


void ControlServerPlugin::readSetting(QSettings& )
{
    return;
}

void ControlServerPlugin::writeSetting(QSettings& )
{
    return;
}
void ControlServerPlugin::show()
{
    return;
}

void ControlServerPlugin::refresh()
{
    return;
}

//Q_EXPORT_PLUGIN2(ControlServer, ControlServerPlugin);
