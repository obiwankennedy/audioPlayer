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
#include "pl_mp3file.h"
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>

#include <QDebug>

/*PL_Mp3File::PL_Mp3File()
  : PL_AudioFile(),fields(NULL)
{
  linked=false;
}*/
PL_Mp3File::PL_Mp3File(QString& uri,SongFields* fields)
  :PL_AudioFile(uri),fields(NULL)
{
  mode=0;
  linked=false;
  this->uri=&uri;
  this->fields=fields;
  header=NULL;

}

PL_Mp3File::~PL_Mp3File()
{

}
int PL_Mp3File::getDuration()
{
  if((fields->duration==-1)||(mode))
  {
    
      if(!linked)
        link();

      
      
      
     
      
    fields->duration = Mp3tagger->getValue(TIME).toInt();
    
    
   /* if(!ok)
    {
      fields->duration=-1;
      if(header == NULL)
        parseHeader();
      
      if(header!= NULL) 
      fields->duration=(header->time*1000);
    }*/
    
    
  }
  return  fields->duration;
}
QString* PL_Mp3File::getTitle() 
{
  if((fields->Title.isNull())||(mode))
  {
    if(!linked)
      link();
  
    fields->Title = Mp3tagger->getValue(TITLE).toString();
  }
  
  if(fields->Title.isEmpty())
  {
    
    QFileInfo a(*this);
    
    

    QStringList ab = a.fileName().split(".");
    if (ab.size() > 0) 
    {
      fields->Title = ab[ab.size()-2]; 
      
    }
  }
  
  
  return &fields->Title;
}
QString* PL_Mp3File::getArtist()
{ 
  if((fields->Artist.isNull())||(mode))
  {
    if(!linked)
      link();
    fields->Artist = Mp3tagger->getValue(ARTIST).toString();
  }
  return &fields->Artist;
}
int PL_Mp3File::getGenre() 
{
 
  if((fields->genre==-1)||(mode))
  {
   
      if(!linked)
        link();
      
    QString a = Mp3tagger->getValue(GENRE).toString();
    
    bool ok;
    
    QRegExp rxlen("(\\d+)");
    int pos = rxlen.indexIn(a);
    if (pos > -1) {
      a = rxlen.cap(1);
      
    }
    fields->genre=a.toInt(&ok,10);
    if(!ok)
    fields->genre=-1;
  }
  return fields->genre;
}

QString* PL_Mp3File::getAlbumtitle() 
{
  if((fields->album.isNull())||(mode))
  {
    if(!linked)
      link();
    
    fields->album =Mp3tagger->getValue(ALBUM).toString();
  }
  return &fields->album;
}
QString* PL_Mp3File::getComment() 
{
  if((fields->Comment.isNull())||(mode))
  {
    if(!linked)
      link();
    
    fields->Comment = Mp3tagger->getValue(COMMENT).toString();
  }
  return &fields->Comment;
  
}
int PL_Mp3File::getYear() 
{
  if((fields->Year==-1)||(mode))
  {
   
    if(!linked)
      link();
      
   fields->Year = Mp3tagger->getValue(YEAR).toInt();

  }
  
  return fields->Year;
}   
int PL_Mp3File::getBitrate() 
{
  
  
  if((fields->Bitrate==-1)||(mode))
  {
    if(!linked)
      link();
        
    
    if(header == NULL)
      parseHeader();
        
    if((header != NULL)&&(header->bitrate>0))
      fields->Bitrate = header->bitrate;
    else if(header != NULL)
      fields->Bitrate = header->vbr_bitrate;
  } 
  
  return fields->Bitrate;
}
int PL_Mp3File::getTrack()
{
    if((fields->Year==-1)||(mode))
    {

      if(!linked)
        link();

      fields->track = Mp3tagger->getValue(TRACK).toInt();

    }
    return fields->track;
}

QStringList* PL_Mp3File::getgenres()
{
  return  Mp3tagger->getgenres();
}
void PL_Mp3File::setTitle(QString p)
{

  (fields->Title) = p;
}
void PL_Mp3File::setArtist(QString p)
{

  fields->Artist = p;
}
void PL_Mp3File::setGenre(int p)
{
  fields->genre = p;
}
void PL_Mp3File::setYear(int p)
{
  fields->Year = p;
}
void PL_Mp3File::setAlbumtitle(QString p)
{

  fields->album = p;
}

void PL_Mp3File::setComment(QString p)
{

  fields->Comment = p;
}
void PL_Mp3File::setTrack(int p)
{
    fields->track = p;

}


bool PL_Mp3File::is_linked()
{
  
  return linked;
  
}
void PL_Mp3File::link()
{
  //qDebug() << *uri;
  Mp3tagger = new PL_TaggerID3(uri);
  linked=true;
}
QImage& PL_Mp3File::getPicture()
{
    if((fields->m_image.isNull())||(mode))
    {

      if(!linked)
        link();

     fields->m_image = Mp3tagger->getValue(PICTURE).value<QImage>();

    }
    return fields->m_image;
}

void PL_Mp3File::setValue(dataColumn x,QVariant& value,bool replace)
{
  if(!linked)
    link();
  Mp3tagger->setValue(x,value,replace);
 bool a;
  switch(x)
  {
  case TITLE:
    setTitle(value.toString());
    break;
  case ARTIST:
    setArtist(value.toString());
    break;
  case ALBUM:
    setAlbumtitle(value.toString());
    break;
  case GENRE:
    setGenre(value.toInt(&a));
    break;
 case COMMENT:
    setComment(value.toString());
    break;
  case YEAR:
    setYear(value.toInt(&a));
    break;
  case TRACK:
    setTrack(value.toInt(&a));
    break;
  case TIME:
  case BITRATE:
  case PICTURE:
    break;
  }
  
 
}
void PL_Mp3File::readering(QDataStream & in)
{
  in >> (fields->Title);
  in >> (fields->Artist);
  in >> (fields->duration);
  in >> (fields->Year);
  in >> (fields->genre);
  in >> (fields->album);
  in >> (fields->Comment);
  in>> (fields->Bitrate);
  in>> (fields->lyrics);

}
void PL_Mp3File::writting(QDataStream & out) const
{

  out     << (fields->Title.simplified())
          << (fields->Artist.simplified())  
          << (fields->duration) 
          << (fields->Year)  
          << (fields->genre) 
          << (fields->album.simplified()) 
          <<(fields->Comment.simplified()) 
          << (fields->Bitrate) 
          << (fields->lyrics.simplified());
}
void PL_Mp3File::ForceTagReading()
{
  mode=1;
}
void PL_Mp3File::parseHeader()
{
  header = Mp3tagger->GetMp3HeaderInfo();
}


