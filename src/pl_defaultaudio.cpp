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
#include "pl_defaultaudio.h"
#include <QFileInfo>
#include <QStringList>
#include <QDebug>

PL_DefaultAudio::PL_DefaultAudio(QString& uri,Song* fields)
  : PL_AudioFile(uri),fields(NULL)
{
  this->uri=&uri;
  this->fields=fields;
}

PL_DefaultAudio::~PL_DefaultAudio() 
{
}

int PL_DefaultAudio::getDuration() const
{
  fields->setDuration(-1);
  return fields->getDuration();
}
const QString& PL_DefaultAudio::getTitle() const
{

  #ifdef HAVE_PHONON
  if((fields->getTitle().isEmpty())/*&&(metaData!=NULL)*/)
  {

    //fields->Title = metaData->value("TITLE");
     if (fields->getTitle() == "")
     {
     	QFileInfo a(*this);
    
    

    	QStringList ab = a.fileName().split(".");
    	if (ab.size() > 0) 
    	{
          fields->setTitle(ab[0]);
      
    	}
    }
    
  }
  #endif
  return fields->getTitle();
}
    
const QString& PL_DefaultAudio::getArtist() const
{
/*#ifdef HAVE_PHONON
         if((fields->Artist.isEmpty())&&(metaData!=NULL))
         {

            fields->Artist = metaData->value("ARTIST");
           }
  #endif*/
  return fields->getArtistName();
}
int PL_DefaultAudio::getGenre() const
{
   /* if((fields->genre)&&(metaData!=NULL))
  {
   // fields->genre = metaData->value("GENRE");
   }*/
  return fields->getGenre();
}
int PL_DefaultAudio::getYear() const
{
  return fields->getYear();
}
const QString& PL_DefaultAudio::getAlbumtitle() const
{
    /*#ifdef HAVE_PHONON
    if((fields->album.isEmpty())&&(metaData!=NULL))
    {
    fields->album = metaData->value("ALBUM");
    }
  #endif*/
  return fields->getAlbum();
}
const QString& PL_DefaultAudio::getComment()  const
{

/*#ifdef HAVE_PHONON
        if((fields->Comment.isEmpty())&&(metaData!=NULL))
        {
        fields->Comment = metaData->value("DESCRIPTION");
       }
        #endif*/
  return fields->getComment();

}

const QImage& PL_DefaultAudio::getPicture() const
{
    return fields->getImage();
}

int PL_DefaultAudio::getBitrate()const
{
 return -1;         
}

void PL_DefaultAudio::setTitle(QString /*p*/)
{
  return;
}
    void PL_DefaultAudio::setArtist(QString /*p*/)
{
  return;
}
    void PL_DefaultAudio::setGenre(int /*p*/)
{
  return;
}
void PL_DefaultAudio::setAlbumtitle(QString /*p*/)
{
  return;
}
void PL_DefaultAudio::setComment(QString /*p*/)
{
  return;
}
void PL_DefaultAudio::setValue(DataField/* x*/,QVariant& /*value*/,bool /*replace*/)
{
  return;
}

void PL_DefaultAudio::setYear(int /*p*/)
{
  return;
}
void PL_DefaultAudio::ForceTagReading()
{
  return;
}
int PL_DefaultAudio::getTrack() const
{
    return fields->getTrackNumber();
}
void PL_DefaultAudio::setTrack(int p)
{
    fields->setTrackNumber(p);
}

void PL_DefaultAudio::readData(QDataStream & in)
{
    /// @warning readData
  //in >> fields ;
}
void PL_DefaultAudio::writting(QDataStream & out) const
{
  out << fields ;
}
