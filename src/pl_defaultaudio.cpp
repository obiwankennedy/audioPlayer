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
#include <QDebug>
#include <QFileInfo>
#include <QStringList>

PL_DefaultAudio::PL_DefaultAudio(QString& uri, SongFields* fields) : PL_AudioFile(uri), fields(NULL)
{
    this->uri= &uri;
    this->fields= fields;
#ifdef HAVE_PHONON
    /* metaInformationResolver = NULL;
      metaData =NULL;*/
    /* if(uri.endsWith("wma"))
     {
         qDebug()  << uri <<endl;
       metaInformationResolver = new Phonon::MediaObject();
           metaInformationResolver->setCurrentSource(Phonon::MediaSource(uri));
           QObject::connect(metaInformationResolver,SIGNAL(metaDataChanged()),this,SLOT(setMetaData()));
           metaData =NULL;
       }*/
#endif
}
/*#ifdef HAVE_PHONON
void PL_DefaultAudio::setMetaData()
{
    if(metaInformationResolver!=NULL){
    metaData = new QMap<QString,QString>(metaInformationResolver->metaData());
    delete metaInformationResolver;
}

#endif*/
PL_DefaultAudio::~PL_DefaultAudio() {}

int PL_DefaultAudio::getDuration()
{
    fields->duration= -1;
    return fields->duration;
}
QString* PL_DefaultAudio::getTitle()
{
#ifdef HAVE_PHONON
    if((fields->Title.isEmpty()) /*&&(metaData!=NULL)*/)
    {
        // fields->Title = metaData->value("TITLE");
        if(fields->Title == "")
        {
            QFileInfo a(file());

            QStringList ab= a.fileName().split(".");
            if(ab.size() > 0)
            {
                fields->Title= ab[0];
            }
        }

        /* setMetaArtist (media->metaData("ARTIST"     ));
     setMetaAlbum  (media->metaData("ALBUM"      ));
     setMetaTitle  (media->metaData("TITLE"      ));
     setMetaDate   (media->metaData("DATE"       ));
     setMetaGenre  (media->metaData("GENRE"      ));
     setMetaTrack  (media->metaData("TRACKNUMBER"));
     setMetaComment(media->metaData("DESCRIPTION"));*/
    }
#endif
    return &fields->Title;
}

QString* PL_DefaultAudio::getArtist()
{
    /*#ifdef HAVE_PHONON
             if((fields->Artist.isEmpty())&&(metaData!=NULL))
             {

                fields->Artist = metaData->value("ARTIST");
               }
      #endif*/
    return &fields->Artist;
}
int PL_DefaultAudio::getGenre()
{
    /* if((fields->genre)&&(metaData!=NULL))
   {
    // fields->genre = metaData->value("GENRE");
    }*/
    return fields->genre;
}
int PL_DefaultAudio::getYear()
{
    return fields->Year;
}
QString* PL_DefaultAudio::getAlbumtitle()
{
    /*#ifdef HAVE_PHONON
    if((fields->album.isEmpty())&&(metaData!=NULL))
    {
    fields->album = metaData->value("ALBUM");
    }
  #endif*/
    return &fields->album;
}
QString* PL_DefaultAudio::getComment()
{
    /*#ifdef HAVE_PHONON
            if((fields->Comment.isEmpty())&&(metaData!=NULL))
            {
            fields->Comment = metaData->value("DESCRIPTION");
           }
            #endif*/
    return &fields->Comment;
}

QImage& PL_DefaultAudio::getPicture()
{
    return fields->m_image;
}

int PL_DefaultAudio::getBitrate()
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
void PL_DefaultAudio::setValue(dataColumn /* x*/, QVariant& /*value*/, bool /*replace*/)
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
int PL_DefaultAudio::getTrack()
{
    return fields->track;
}
void PL_DefaultAudio::setTrack(int p)
{
    fields->track= p;
}

void PL_DefaultAudio::readering(QDataStream& in)
{
    in >> (fields->Title);
    in >> (fields->Artist);
    in >> (fields->duration);
    in >> (fields->Year);
    in >> (fields->genre);
    in >> (fields->album);
    in >> (fields->Comment);
    in >> (fields->Bitrate);
}
void PL_DefaultAudio::writting(QDataStream& out) const
{
    out << (fields->Title.simplified());
    out << (fields->Artist.simplified());
    out << (fields->duration);
    out << (fields->Year);
    out << (fields->genre);
    out << (fields->album.simplified());
    out << (fields->Comment.simplified());
    out << (fields->Bitrate);
}
