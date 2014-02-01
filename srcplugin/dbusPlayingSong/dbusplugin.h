#ifndef DBUSPLUGIN_H
#define DBUSPLUGIN_H

#include <QObject>
#include <songplugin.h>


class DbusPlugin : public QObject,public SongInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.playlistgenerator.SongInterface.dbus" FILE "dbus.json")
    Q_INTERFACES(SongInterface)

private:

    const SongFields* m_p;
    QAction* m_action;

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
