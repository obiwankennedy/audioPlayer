/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
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
#include "defaultdecorator.h"
#include "playlistitem.h"
#include "pl_defaultaudio.h"
Defaultdecorator::Defaultdecorator()
{
   fi = new QFileInfo;
}

Defaultdecorator::Defaultdecorator(PlaylistItem* _item)
  : ItemDecorator(_item)
{

  fi = new QFileInfo;
}

Defaultdecorator::~Defaultdecorator()
{
}

QVariant Defaultdecorator::getMember(DataField x) const
{

  
  if(item==NULL)
    return QVariant();

  //PL_DefaultAudio* tmp =(PL_DefaultAudio*) item->getMediaFile();

    Song* song = item->getSong();

  switch(x)
  {
    case TITLE:
    {
      return song->getTitle();
    }
    case ARTIST:
      return song->getArtistName();
    case TIME:
      return song->getDuration();
    case ALBUM:
      return song->getAlbum();
    case GENRE:
      return song->getGenre();
    case TRACK:
        return song->getTrackNumber();
    case COMMENT:
      return song->getComment();
    case YEAR:
      return song->getYear();
    case PICTURE:
      return song->getImage();
    case BITRATE:
      return song->getBitrate();
  default:
      return QVariant();  
  }
  return QVariant(); 
   
      

}
void Defaultdecorator::setValue(DataField x,QVariant& value,bool )
{
    Song* song = item->getSong();
  switch(x)
  {
    case TITLE:
      song->setTitle(value.toString());
      break;
    case ARTIST:
      song->setArtistName(value.toString());
      break;
    case YEAR:
      song->setYear( value.toInt());
      break;
    case ALBUM:
      song->setAlbum(value.toString());
      break;
    case BITRATE:
    case PICTURE:
    case TIME:
      break;
    case COMMENT:
      song->setComment(value.toString());
      break;
    case GENRE:
      song->setGenre(value.toInt());
      break;
  case TRACK:
      song->setTrackNumber(value.toInt());

  }

  return;
}
QStringList* Defaultdecorator::getgenres()
{
  return new QStringList;
}
void Defaultdecorator::setItem(PlaylistItem* _item) 
{
  item = _item;
}
PlaylistItem* Defaultdecorator::getItem() 
{
  return item;
}
void Defaultdecorator::ForceTagReading()
{
  return;
}
