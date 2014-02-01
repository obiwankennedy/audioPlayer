//PlayListGenerator : Hivaf4ie
#include "lyricsfinder.h"
#include <QDomDocument>
#include <QDebug>
#include <QDomNamedNodeMap>
#include <QtGlobal>
#include <QMessageBox>
#include <QProcess>
#include <QNetworkReply>
#include <QNetworkRequest>

LyricsFinder::LyricsFinder()
{
    http = new QNetworkAccessManager();
    http2 = new QNetworkAccessManager();

    fields = NULL;

    m_search= new QByteArray;
    //http->setHost("api.leoslyrics.com");
    //http2->setHost("api.leoslyrics.com");


    QObject::connect(http,SIGNAL(finished(QNetworkReply *)),
             this,SLOT(readLyrics(QNetworkReply *)));

    QObject::connect(http2,SIGNAL(finished(QNetworkReply *)),
             this,SLOT(readLyrics( QNetworkReply *)));

   /* QObject::connect(http2,SIGNAL(requestFinished(int,bool)),
             this,SLOT(httpRequestFinished(int,bool)));

    QObject::connect(http,SIGNAL(requestFinished(int,bool)),
             this,SLOT(httpRequestFinished2(int,bool)));*/

   //  m_receiving = false;
      m_lyrics = new QString;
      links =  new QStringList;

}
void LyricsFinder::search()
{

    if(fields!=NULL)
    {
        QString artist= fields->Artist;
        QString title = fields->Title;
        QString url=QString("http://www.leoslyrics.com/%1/%2-lyrics/").arg(artist.replace(' ',"-")).arg(title.replace(' ',"-"));

        //qDebug() << url.toLower();

        QString ques = QString(QUrl(url.toLower()).toEncoded());

        m_search->clear();
        links->clear();
        m_lyrics->clear();
        http->get(QNetworkRequest(QUrl(ques)));

    }

}
QString* LyricsFinder::GetLyrics()
{

    if(m_lyrics == NULL)
        return  new QString(QObject::tr("no lyrics found"));

    return m_lyrics;

}
void LyricsFinder::setfields(const SongFields * s)
{
    Q_ASSERT(s!=NULL);
    fields = s;
    m_lyrics->clear();

}
bool LyricsFinder::foundLyrics()
{
    return m_isFound;

}
void LyricsFinder::readLyrics(QNetworkReply *p)
{


    QByteArray* a = new QByteArray;
    *a = p->readAll();

    QString toto(*a);



    m_lyrics->append(toto.replace("&#xD;",""));


    if(m_lyrics->contains("<div ondragstart=\"return false;\" onselectstart=\"return false;\" oncontextmenu=\"return false;\">")&&m_lyrics->contains("</div>"))
    {
        QRegExp exp("<div ondragstart=\"return false;\" onselectstart=\"return false;\" oncontextmenu=\"return false;\">(.*)</div>");
         exp.setMinimal(true);

        exp.indexIn(*m_lyrics,0);

        *m_lyrics = exp.cap(1);


        m_isFound = true;
        //*lyrics = toto;
        emit lyricsready();

    }


}
 void LyricsFinder::readResponseHeader(QNetworkReply *p)
 {

    m_search->append(p->readAll());


   QRegExp exp("hid=\"([^< ]*)\"");
   int pos = 0;
   QString a(*m_search);

    while ((pos = exp.indexIn(a, pos)) != -1)
   {
       links->append(exp.cap(1));
       pos += exp.matchedLength();
   }

   if(links->size() > 0)
   {
           QString ques="http://api.leoslyrics.com/api_lyrics.php?auth=PlayListGenerator&hid="+links->at(0);

           ques = QString(QUrl(ques).toEncoded());

           http2->get(QNetworkRequest(QUrl(ques)));
   }
   else
   {
       m_isFound = false;
       *m_lyrics = tr("No lyrics found");

       emit lyricsready();
   }

 }

 void LyricsFinder::updateDataReadProgress(int bytesRead, int totalBytes)
 {
     Q_UNUSED(bytesRead);
     Q_UNUSED(totalBytes);
     if (httpRequestAborted)
         return;


 }

 void LyricsFinder::enableDownloadButton()
 {

 }

 void LyricsFinder::slotAuthenticationRequired(const QString &hostName, quint16, QAuthenticator *authenticator)
 {
     Q_UNUSED(hostName);
     Q_UNUSED(authenticator);

 }

