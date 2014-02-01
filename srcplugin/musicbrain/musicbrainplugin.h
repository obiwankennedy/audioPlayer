#ifndef MUSICBRAINPLUGIN_H
#define MUSICBRAINPLUGIN_H

#include <QObject>
#include <songlistplugin.h>
#include <QFutureWatcher>

#include "musicbrainzclient.h"

class MusicDnsClient;

class MusicBrainPlugin : public QObject,public SongListInterface
{
    Q_OBJECT

    Q_INTERFACES(SongListInterface)

private:

    const SongFields* m_p;
    QAction* m_action;
    QFutureWatcher<QString>* fingerprint_watcher_;
    MusicDnsClient* m_musicdns_client;
    MusicBrainzClient* musicbrainz_client_;

public:

    virtual void SetSong(SongFields* p,QString& uri);
    virtual QString getName();
    virtual QAction* getAction();
    virtual void stopped();
    virtual QDockWidget* getWidget();
    virtual bool hasUI();
    virtual bool isVisible();
    virtual Qt::DockWidgetArea orientation();


    virtual void readSetting();
    virtual void writeSetting();


public slots:
      virtual void show();
      virtual void refresh();
      virtual void FingerprintFound(int);
private:
  static QString GetFingerprint(const QString& song);

     // void onError( QProcess::ProcessError error);
};

#endif // MUSICBRAINPLUGIN_Hy
