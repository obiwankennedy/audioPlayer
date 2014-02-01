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
#include "mp3decorator.h"
#include "playlistitem.h"
#include "factory/pl_mp3file.h"
Mp3Decorator::Mp3Decorator()
 : ItemDecorator()
{
  
}
Mp3Decorator::Mp3Decorator(PlaylistItem* _item)
  : ItemDecorator(_item)
{
  
}
Mp3Decorator::~Mp3Decorator()
{
  
}
QVariant Mp3Decorator::getMember(dataColumn x) const
{

  PL_Mp3File* tmp =(PL_Mp3File*) item->getMediaFile();
  
  if(tmp==NULL)
    return QVariant();
  


  switch(x)
  {
    case TITLE:
    {
      return (*tmp->getTitle());
    }
    case ARTIST:
      return (*tmp->getArtist());
    case TIME:
      return tmp->getDuration();
    case ALBUM:
      return (*tmp->getAlbumtitle());
    case GENRE:
      return tmp->getGenre();
    case COMMENT:
      return (*tmp->getComment());
    case YEAR:
      return tmp->getYear();
    case BITRATE:
      return tmp->getBitrate();
    case TRACK:
     return tmp->getTrack();
        
  }
  return QVariant();  
}

void Mp3Decorator::setValue(dataColumn x,QVariant& value,bool replace)
{
  PL_Mp3File* tmp =(PL_Mp3File*) item->getMediaFile();
  tmp->setValue(x,value,replace);
}


QStringList* Mp3Decorator::getgenres()
{
  PL_Mp3File* tmp =(PL_Mp3File*) item->getMediaFile();
  return tmp->getgenres();
}
void Mp3Decorator::setItem(PlaylistItem* _item) 
{
  item=_item;
}
PlaylistItem* Mp3Decorator::getItem() const
{
  return item;
}
void Mp3Decorator::ForceTagReading()
{
  PL_Mp3File* tmp =(PL_Mp3File*) item->getMediaFile();
  tmp->ForceTagReading();
}
