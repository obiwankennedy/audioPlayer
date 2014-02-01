#include "musicbrainplugin.h"
#include <QtGui>
#include <QDebug>
#include <QString>
#include "musicdnsclient.h"
#include "fingerprinter.h"

bool MusicBrainPlugin::hasUI()
{
    return false;
}
QString MusicBrainPlugin::GetFingerprint(const QString& song)
{
  return Fingerprinter(song).CreateFingerprint();
}

void MusicBrainPlugin::SetSong(SongFields* p,QString& uri)
{
    //m_proc = new QProcess;

    m_musicdns_client=new MusicDnsClient(this);

    connect(m_musicdns_client, SIGNAL(Finished(int,QString)), SLOT(PuidFound(int,QString)));
     connect(musicbrainz_client_, SIGNAL(Finished(int,MusicBrainzClient::ResultList)), SLOT(TagsFetched(int,MusicBrainzClient::ResultList)));

    if(!m_action->isChecked())
    {
        stopped();
        return;
    }

    m_p = p;

    QStringList list;
    list << uri;
    QFuture<QString> future = QtConcurrent::mapped(list, GetFingerprint);
    fingerprint_watcher_ = new QFutureWatcher<QString>(this);
    fingerprint_watcher_->setFuture(future);
    connect(fingerprint_watcher_, SIGNAL(resultReadyAt(int)), SLOT(FingerprintFound(int)));


}
void MusicBrainPlugin::stopped()
{



}

QString MusicBrainPlugin::getName()
{

    m_action = new QAction("Fill out Tags",this);


    m_action->setShortcut(tr("Ctrl+T"));
    m_action->setStatusTip(tr("Send informations about the played song to MusicBrain"));


    return tr("MusicBrain");
}
void MusicBrainPlugin::FingerprintFound(int print)
{
    QFutureWatcher<QString>* watcher = reinterpret_cast<QFutureWatcher<QString>*>(sender());
      if (!watcher /* || index >= songs_.count()*/) {
        return;
      }

      const QString fingerprint = watcher->resultAt(print);

      if (fingerprint.isEmpty()) {
        //emit ResultAvailable(song, SongList());
        return;
      }
      m_musicdns_client->Start(print, fingerprint, m_p->duration);

}

QAction* MusicBrainPlugin::getAction()
{
    return m_action;
}

QDockWidget* MusicBrainPlugin::getWidget()
{

    return NULL;
}
bool MusicBrainPlugin::isVisible()
{
    return false;
}

Qt::DockWidgetArea MusicBrainPlugin::orientation()
{
    return Qt::BottomDockWidgetArea;
}


void MusicBrainPlugin::readSetting()
{
    return;
}

void MusicBrainPlugin::writeSetting()
{
    return;
}
void MusicBrainPlugin::show()
{
return;
}

void MusicBrainPlugin::refresh()
{
    return;
}

Q_EXPORT_PLUGIN2(musicbrain, MusicBrainPlugin);
