/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec                                *
 *   renaud.guezennec@gmail.com                                            *
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
#include "playlistitem.h"
#include "itemdecorator.h"
#include <QTextStream>  
#include <QDebug>

PlaylistItem::PlaylistItem()
{
    //m_song = new Song;
    facade = MediaFacade::getInstance();
    urichanged = false;
    qRegisterMetaTypeStreamOperators<PlaylistItem>("PlaylistItem");
}

PlaylistItem *PlaylistItem::ms_currentPlayedItem = NULL;

PlaylistItem::~PlaylistItem()
{

    facade = NULL;
    // delete m_song;
    //delete m_mediaFile;

}

PlaylistItem::PlaylistItem(const PlaylistItem& original)
{
    this->facade = MediaFacade::getInstance();
    this->m_mediaFile = NULL;
    m_song = *original.getConstSong();
    findmedia();
}
//MediaFacade *PlaylistItem::facade = NULL;
QString PlaylistItem::getReadableTitle()
{
   // return QString("%1 - %2").arg(m_song.getArtistName()).arg(m_song.getTitle());
   return QString("%1 - %2").arg(m_mediaFile->getArtist()).arg(m_mediaFile->getTitle());
}
const QString PlaylistItem::getURI() const
{

    return m_song.getUri();

}
const QImage& PlaylistItem::getPicture()
{
    m_song.setImage(getKey()->getMember(PICTURE).value<QImage>());

    return m_song.getImage();
}

void PlaylistItem::setURI(QString & p) 
{
    m_song.setUri(p);
    urichanged = true;
    findmedia();
}


QString PlaylistItem::toString()
{


    if((m_song.getTitle().isNull()))
    {
        m_song.setTitle(getKey()->getMember(TITLE).toString());
    }
    if((m_song.getArtistName().isNull()))
    {
        m_song.setArtistName(getKey()->getMember(ARTIST).toString());
    }


    return QString(m_song.getArtistName()+" - "+m_song.getTitle());

}
const QString PlaylistItem::getExt() const
{
    return buildExt();
}
void PlaylistItem::SetExt(QString& p)
{

}


QString PlaylistItem::buildExt()  const
{
    int a;

    QString ext("#EXTINF:%1, %2 - %3");

    if(m_song.getDuration()<0)
        a = 0;
    else
        a=m_song.getDuration();
    a/=1000;


    return ext.arg(QString::number(a)).arg(m_song.getArtistName().simplified()).arg(m_song.getTitle().simplified());


}
void PlaylistItem::exploseExt()
{
}
PL_MediaFile* PlaylistItem::getMediaFile()
{
    return m_mediaFile;
}

ItemDecorator* PlaylistItem::getKey() const
{
    return key;
}
void PlaylistItem::ForceTagReading()
{
    key->setItem(this);
    key->ForceTagReading();
}
bool PlaylistItem::isReading() const
{
    return (ms_currentPlayedItem == this);
}
void PlaylistItem::setReading(bool t)
{
    if(t)
        ms_currentPlayedItem = this;


}
void PlaylistItem::acceptVisitor(VisitorMedia* visitor)
{
  visitor->visitMedia(this);
}
Song* PlaylistItem::getSong()
{
    return &m_song;
}

const Song* PlaylistItem::getConstSong() const
{
    return &m_song;
}

QTextStream& operator<<(QTextStream& Out, const PlaylistItem& B) 
{ 


    Out << B.getExt()<< endl;
    Out << B.getURI()<< endl;

    return Out;
}

QTextStream& operator>>(QTextStream& is,PlaylistItem& B)
{
    QString a;

    a= is.readLine();
    if(!a.startsWith("#EXTINF",Qt::CaseSensitive))
    {
        B.getSong()->setUri(a);
    }
    else
    {
        B.getSong()->setUri(is.readLine());
    }
    B.findmedia();
    return is;


}

QDataStream& operator<<(QDataStream& Out, const PlaylistItem& B) 
{ 

    QString a;
    Out << B.getURI();
    Out << (B.m_song);

    return Out;
}

QDataStream& operator>>(QDataStream& is,PlaylistItem& B)
{
    QString a;
    is >>a;
    B.setURI(a);
    is >> (B.m_song);
    key->setItem(*B);
    return is;


}
