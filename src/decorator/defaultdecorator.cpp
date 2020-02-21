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
#include "pl_defaultaudio.h"
#include "playlistitem.h"
Defaultdecorator::Defaultdecorator()
{
    fi= new QFileInfo;
}

Defaultdecorator::Defaultdecorator(PlaylistItem* _item) : ItemDecorator(_item)
{
    fi= new QFileInfo;
}

Defaultdecorator::~Defaultdecorator() {}

QVariant Defaultdecorator::getMember(dataColumn x) const
{
    PL_DefaultAudio* tmp= (PL_DefaultAudio*)item->getMediaFile();

    if(item == NULL)
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
    case TRACK:
        return tmp->getTrack();
    case COMMENT:
    case YEAR:
    case BITRATE:
        return QVariant();
    }
    return QVariant();
}
void Defaultdecorator::setValue(dataColumn x, QVariant& value, bool)
{
    SongFields* sf= item->getFields2();
    switch(x)
    {
    case TITLE:
        sf->Title= value.toString();
        break;
    case ARTIST:
        sf->Artist= value.toString();
        break;
    case YEAR:
        sf->Year= value.toInt();
        break;
    case ALBUM:
        sf->album= value.toString();
        break;
    case BITRATE:
    case TIME:
        break;
    case COMMENT:
        sf->Title= value.toString();
        break;
    case GENRE:
        sf->genre= value.toInt();
        break;
    case TRACK:
        sf->track= value.toInt();
    }

    return;
}
QStringList* Defaultdecorator::getgenres()
{
    return new QStringList;
}
void Defaultdecorator::setItem(PlaylistItem* _item)
{
    item= _item;
}
PlaylistItem* Defaultdecorator::getItem()
{
    return item;
}
void Defaultdecorator::ForceTagReading()
{
    return;
}
