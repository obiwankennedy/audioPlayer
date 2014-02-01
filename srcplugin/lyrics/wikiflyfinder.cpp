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
#include "wikiflyfinder.h"
#include <QDomDocument>
#include <QDebug>
#include <QDomNamedNodeMap>
#include <QtGlobal>
#include <QMessageBox>
#include <QProcess>
#include <QTextDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>


WikiFlyFinder::WikiFlyFinder()
{
    http = new QNetworkAccessManager();


    m_search= new QByteArray;



    QObject::connect(http,SIGNAL(finished(QNetworkReply *)),
             this,SLOT(readResponseHeader( QNetworkReply *)));





   //  m_receiving = false;
      m_lyrics = new QString;
      links =  new QStringList;
}

void WikiFlyFinder::search()
{
     m_isFound = false;


     QString url=QString("http://api.lyricsfly.com/api/api.php?i=09480e0551c7da949-lyricsfreelive.com&a=%1&t=%2").arg(fields->Artist).arg(fields->Title);

     //dead
        //5618147225-zikpot.fr

     //not used yet
     //55614845584-themusicmesh.com
     QString ques = QString(QUrl(url).toEncoded());

     m_search->clear();
     links->clear();
     http->get(QNetworkRequest(QUrl(ques)));
}
QString* WikiFlyFinder::GetLyrics()
{

    if(m_lyrics == NULL)
        return  new QString(QObject::tr("no lyrics found"));

    return m_lyrics;

}
void WikiFlyFinder::setfields(const SongFields * s)
{
    Q_ASSERT(s!=NULL);
    fields = s;

}
bool WikiFlyFinder::foundLyrics()
{
    return m_isFound;

}

 void WikiFlyFinder::readResponseHeader(QNetworkReply * p)
 {
    m_search->append(p->readAll());

    QString a(*m_search);

    if(a.contains("<sg>")&&a.contains("</sg>"))
    {
        QString tmp = a.mid(a.indexOf("<sg>")+4,a.indexOf("</sg>")-a.indexOf("<sg>")-4);

        if(tmp.contains("<tx>")&&tmp.contains("</tx>"))
        {

            QRegExp exp("<tx>([^<]*)</tx>");

            exp.indexIn(tmp,0);

            *m_lyrics = exp.cap(1);

            QTextDocument doc;
            m_lyrics->replace("[br]","<br/>");
            doc.setHtml(*m_lyrics);
            *m_lyrics = doc.toPlainText();

            m_isFound = true;
            emit lyricsready();
        }

    }
 }

 void WikiFlyFinder::updateDataReadProgress(int bytesRead, int totalBytes)
 {
     Q_UNUSED(bytesRead);
     Q_UNUSED(totalBytes);
     /*if (httpRequestAborted)
         return;*/


 }

 void WikiFlyFinder::enableDownloadButton()
 {

 }

 void WikiFlyFinder::slotAuthenticationRequired(const QString &hostName, quint16, QAuthenticator *authenticator)
 {
     Q_UNUSED(hostName);
     Q_UNUSED(authenticator);

 }

