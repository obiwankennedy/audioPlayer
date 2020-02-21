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
#include "factorymp3.h"
#include "pl_mp3file.h"
FactoryMP3::FactoryMP3() {}

FactoryMP3::~FactoryMP3() {}
FactoryMP3* FactoryMP3::singleton= NULL;

FactoryMP3* FactoryMP3::getInstance()
{
    if(singleton == NULL)
        singleton= new FactoryMP3;

    return singleton;
}
PL_MediaFile* FactoryMP3::buildMedia(QString& uri, SongFields* fields)
{
    PL_Mp3File* tmp= new PL_Mp3File(uri, fields);

    return tmp;
}
