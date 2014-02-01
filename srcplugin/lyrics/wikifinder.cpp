/***************************************************************************
 *   Copyright (C) 2009 by Renaud Guezennec   *
 *   renaud.guezennec@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "wikifinder.h"
#include <QDomDocument>
#include <QDebug>
#include <QDomNamedNodeMap>
#include <QtGlobal>
#include <QMessageBox>
#include <QProcess>
#include <QTextDocument>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>

WikiFinder::WikiFinder()
{
    http = new QNetworkAccessManager();


    m_search= new QByteArray;




    QObject::connect(http,SIGNAL(finished(QNetworkReply *)),
             this,SLOT(readResponseHeader( QNetworkReply *)));





      m_lyrics = new QString;
      links =  new QStringList;
}


void WikiFinder::search()
{
/*if((!fields->Artist.isEmpty())&&(!fields->Title.isEmpty()))
    {*/
     m_isFound = false;

     QString artist= fields->Artist;
     QString title = fields->Title;
     QString url=QString("http://lyrics.wikia.com/%1:%2").arg(artist).arg(title);

     QString ques = QString(QUrl(url).toEncoded());

     m_search->clear();
     links->clear();

     http->get(QNetworkRequest(QUrl(ques)));
    //}
}
QString* WikiFinder::GetLyrics()
{

    if(m_lyrics == NULL)
        return  new QString(QObject::tr("no lyrics found"));

    return m_lyrics;

}
void WikiFinder::setfields(const SongFields * s)
{
    Q_ASSERT(s!=NULL);
    fields = s;

}
bool WikiFinder::foundLyrics()
{
    return m_isFound;

}

void WikiFinder::httpRequestFinished(int requestId, bool error)
 {
     Q_UNUSED(requestId);
     Q_UNUSED(error);





 }


 void WikiFinder::readResponseHeader(QNetworkReply * p)
 {

    m_search->append(p->readAll());

    QString a(*m_search);
     QRegExp rx2("alt='phone' width='16' height='17'/></a></div>(.*)<!--");
     rx2.setMinimal(true);

     if (rx2.indexIn(a) != -1)
     {
          *m_lyrics = rx2.cap(1);

          m_isFound = true;
          emit lyricsready();
     }


 }

 void WikiFinder::updateDataReadProgress(int bytesRead, int totalBytes)
 {
     Q_UNUSED(bytesRead);
     Q_UNUSED(totalBytes);
     /*if (httpRequestAborted)
         return;*/


 }

 void WikiFinder::enableDownloadButton()
 {

 }

 void WikiFinder::slotAuthenticationRequired(const QString &hostName, quint16, QAuthenticator *authenticator)
 {
     Q_UNUSED(hostName);
     Q_UNUSED(authenticator);

 }

