#include "sendserverplugin.h"


#include <QtGui>
#include <QtWidgets>
#include <QDebug>


bool SendServerPlugin::hasUI()
{
    return false;
}

void SendServerPlugin::SetSong(SongFields* p)
{
    return;
}
void SendServerPlugin::stopped()
{
    
}

QString SendServerPlugin::getName()
{

    m_action = new QAction(tr("Send Server"),this);
    m_external = new ServerThread;
    m_action->setCheckable(true);
    m_action->setChecked(true);
    m_action->setShortcut(tr("Ctrl+R"));
    m_action->setStatusTip(tr("Allow the application to be controlled by external system"));
    //connect(m_action, SIGNAL(triggered()), this, SLOT(toggle()));
    m_external->start();
    return tr("Remote");
}

QAction* SendServerPlugin::getAction()
{
    return m_action;
}

QDockWidget* SendServerPlugin::getWidget()
{
    return NULL;
}
bool SendServerPlugin::isVisible()
{
    return false;
}

Qt::DockWidgetArea SendServerPlugin::orientation()
{
    return Qt::BottomDockWidgetArea;
}


void SendServerPlugin::readSetting(QSettings& )
{
    return;
}

void SendServerPlugin::writeSetting(QSettings& )
{
    return;
}
void SendServerPlugin::show()
{
    return;
}

void SendServerPlugin::refresh()
{
    return;
}


