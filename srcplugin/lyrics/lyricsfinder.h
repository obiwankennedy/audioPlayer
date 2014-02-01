#ifndef LYRICSFINDER_H
#define LYRICSFINDER_H


#include <QUrl>
#include <QString>
#include <QNetworkAccessManager>

#include <data.h>
#include "AbstractLyricsFinder.h"
class LyricsFinder : public AbstractLyricsFinder
{
    Q_OBJECT
    const SongFields * fields;
    QNetworkAccessManager *http;
    QNetworkAccessManager *http2;
    bool m_receiving;
    QStringList* links;

    QByteArray* m_search;

     int httpGetId;
     bool httpRequestAborted;
    //QTcpSocket* tpcsocket;
public:
    LyricsFinder();
    void setfields(const SongFields * s);
    void search();
    virtual bool foundLyrics();
public slots:

    void readAnswer();
    void readAnswer2();
    //void finish(bool);
    QString* GetLyrics();
  signals:
    void lyricsready();

private slots:
   /*  void downloadFile();
     void cancelDownload();*/

     void readResponseHeader(QNetworkReply *);
     void readLyrics(QNetworkReply *p);
     void updateDataReadProgress(int bytesRead, int totalBytes);
     void enableDownloadButton();
     void slotAuthenticationRequired(const QString &, quint16, QAuthenticator *);



};

#endif // LYRICSFINDER_H
