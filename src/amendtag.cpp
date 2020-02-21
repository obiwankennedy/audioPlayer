/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
 *   http://renaudguezennec.homelinux.org/accueil,3.html   *
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
#include "amendtag.h"

AmendTag::AmendTag(QString artist, bool bartist, QString title, bool btitre, QString album, bool balbum, int genre,
    bool bgenre, QString uri, bool buri, QString comment, bool bcom, QString year, bool byear, bool replace)
    : VisitorMedia()
{
    myPlaylist= Playlist::getInstance();

    if(btitre)
        newtitle= &title;
    else
        newtitle= NULL;

    if(bartist)
        newartist= &artist;
    else
        newartist= NULL;

    if(balbum)
        newalbum= &album;
    else
        newalbum= NULL;

    if(bgenre)
        newgenre= genre;
    else
        newgenre= -1;

    if(bcom)
        newcomment= &comment;
    else
        newcomment= NULL;

    if(buri)
    {
        newuri= new QString;
        (*newuri)= uri;
    }
    else
        (newuri)= NULL;

    if(byear)
        newyear= &year;
    else
        newyear= NULL;

    this->replace= replace;
}

AmendTag::~AmendTag() {}

void AmendTag::visitMedia(ItemDecorator* media)
{
    if(newuri != NULL)
    {
        media->getItem()->setURI(*newuri);
        media->ForceTagReading();
    }

    if(newtitle != NULL)
    {
        QVariant title(*newtitle);
        media->setValue(TITLE, title, true);
    }

    if(newartist != NULL)
    {
        QVariant artist(*newartist);
        media->setValue(ARTIST, artist, true);
    }

    if(newalbum != NULL)
    {
        QVariant album(*newalbum);
        media->setValue(ALBUM, album, true);
    }

    if(newcomment != NULL)
    {
        QVariant comment(*newcomment);
        media->setValue(COMMENT, comment, true);
    }
    if(newyear != NULL)
    {
        QVariant vyear(*newyear);
        media->setValue(YEAR, vyear, true);
    }
    if(newgenre != -1)
    {
        QVariant genre(newgenre);
        media->setValue(GENRE, genre, true);
    }
}
