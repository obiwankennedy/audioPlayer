/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
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
#ifndef WIKIFLYFINDER_H
#define WIKIFLYFINDER_H
#include "AbstractLyricsFinder.h"

#include "AbstractLyricsFinder.h"
#include <QString>
#include <QNetworkAccessManager>

class WikiFlyFinder : public AbstractLyricsFinder
{
    Q_OBJECT
    const SongFields * fields;
    QNetworkAccessManager *http;

    bool m_receiving;
    QStringList* links;

    QByteArray* m_search;
public:
    WikiFlyFinder();
    virtual void setfields(const SongFields * s);
    virtual void search();
    virtual QString* GetLyrics();
    virtual bool foundLyrics();
signals:
    void lyricsready();

private slots:
   /*  void downloadFile();
     void cancelDownload();*/
     //void httpRequestFinished(int requestId, bool error);

     void readResponseHeader(QNetworkReply *);

     void updateDataReadProgress(int bytesRead, int totalBytes);
     void enableDownloadButton();
     void slotAuthenticationRequired(const QString &, quint16, QAuthenticator *);
};

#endif // WIKIFLYFINDER_H