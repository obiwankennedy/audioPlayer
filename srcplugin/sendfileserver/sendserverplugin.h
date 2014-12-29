#ifndef CONTROLSERVERPLUGIN_H
#define CONTROLSERVERPLUGIN_H

#include <QObject>
#include <songplugin.h>
#include "serverthread.h"


class SendServerPlugin : public QObject,public SongInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.playlistgenerator.SongInterface.servercontrol" FILE "servercontrol.json")
    Q_INTERFACES(SongInterface)

private:

/*    const SongFields* m_p;*/
    QAction* m_action;
    ServerThread* m_external;

public:

    virtual void SetSong(SongFields* p);
    virtual QString getName();
    virtual QAction* getAction();
    virtual void stopped();
    virtual QDockWidget* getWidget();
    virtual bool hasUI();
    virtual bool isVisible();
    virtual Qt::DockWidgetArea orientation();


    virtual void readSetting(QSettings& settings);
    virtual void writeSetting(QSettings& settings);


public slots:
      virtual void show();
      virtual void refresh();
     // void onError( QProcess::ProcessError error);
};

#endif // DBUSPLUGIN_H
