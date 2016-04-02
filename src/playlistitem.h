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
#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QString>
#include <QTextStream>
#include <QTextCodec>
#include <QStringList>

#include "factory/pl_mediafile.h"
#include "factory/mediafacade.h"
#include "data.h"
#include "itemdecorator.h"

#include "data/song.h"
/**
    @author Renaud Guezennec
 * \class PlaylistItem
 * \brief represent a playlist item. it is the main data class.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no           
*/

class PlaylistItem
{
  static PlaylistItem* ms_currentPlayedItem;
public:
    PlaylistItem();
    PlaylistItem(const PlaylistItem& original);
    ~PlaylistItem();
    bool isReading() const;
    void setReading(bool t);

    const Song* getConstSong() const;
    Song* getSong();


     const QString getURI() const;
     void setURI(QString & p);
     ItemDecorator* getKey() const;
     const QString getExt() const; 
     void SetExt(QString & p);
     
     QString buildExt() const;
     void exploseExt();
     PL_MediaFile* getMediaFile();
     void ForceTagReading();
     QString getReadableTitle();
     QString toString();
     const QImage& getPicture();
     
     friend QTextStream& operator<<(QTextStream& os,const PlaylistItem&);
     friend QTextStream& operator>>(QTextStream& is,PlaylistItem&);
     friend QDataStream& operator<<(QDataStream& os,const PlaylistItem&);
     friend QDataStream& operator>>(QDataStream& is,PlaylistItem&);

private:
     Song m_song;
};

 Q_DECLARE_METATYPE(PlaylistItem)
 Q_DECLARE_METATYPE(PlaylistItem*)
#endif
