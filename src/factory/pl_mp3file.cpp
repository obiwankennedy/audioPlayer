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
PL_Mp3File::PL_Mp3File(QString& uri,Song* fields)
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
int PL_Mp3File::getDuration() const
{
  if((fields->getDuration()==-1)||(mode))
  {
    
//      if(!linked)
//        link();

      
      
      
     
      
    fields->setDuration(Mp3tagger->getValue(TIME).toInt());
    
    

    
  }
  return  fields->getDuration();
}
const QString& PL_Mp3File::getTitle() const
{
  if((fields->getTitle().isNull())||(mode))
  {
//    if(!linked)
//      link();
  
    fields->setTitle(Mp3tagger->getValue(TITLE).toString());
  }
  
  if(fields->getTitle().isEmpty())
  {
    
    QFileInfo a(*this);
    
    

    QStringList ab = a.fileName().split(".");
    if (ab.size() > 0) 
    {
      fields->setTitle(ab[ab.size()-2]);
      
    }
  }
  
  
  return fields->getTitle();
}
const QString& PL_Mp3File::getArtist() const
{ 
  if((fields->getArtistName().isNull())||(mode))
  {
//    if(!linked)
//      link();
    fields->setArtistName(Mp3tagger->getValue(ARTIST).toString());
  }
  return fields->getArtistName();
}
int PL_Mp3File::getGenre() const
{
 
  if((fields->getGenre()==-1)||(mode))
  {
   
//      if(!linked)
//        link();
      
    QString a = Mp3tagger->getValue(GENRE).toString();
    
    bool ok;
    
    QRegExp rxlen("(\\d+)");
    int pos = rxlen.indexIn(a);
    if (pos > -1) {
      a = rxlen.cap(1);
      
    }
    fields->setGenre(a.toInt(&ok,10));
    if(!ok)
    fields->setGenre(-1);
  }
  return fields->getGenre();
}

const QString& PL_Mp3File::getAlbumtitle() const
{
  if((fields->getAlbum().isNull())||(mode))
  {
    /*if(!linked)
      link();*/
    
    fields->setAlbum(Mp3tagger->getValue(ALBUM).toString());
  }
  return fields->getAlbum();
}
const QString& PL_Mp3File::getComment() const
{
  if((fields->getComment().isNull())||(mode))
  {
//    if(!linked)
//      link();
    
    fields->setComment(Mp3tagger->getValue(COMMENT).toString());
  }
  return fields->getComment();
  
}
int PL_Mp3File::getYear() const
{
  if((fields->getYear()==-1)||(mode))
  {
   
//    if(!linked)
//      link();
      
   fields->setYear(Mp3tagger->getValue(YEAR).toInt());

  }
  
  return fields->getYear();
}   
int PL_Mp3File::getBitrate() const
{
  
  
  if((fields->getBitrate()==-1)||(mode))
  {
//    if(!linked)
//      link();
        
    
//    if(header == NULL)
//      parseHeader();
        
    if((header != NULL)&&(header->bitrate>0))
      fields->setBitrate(header->bitrate);
    else if(header != NULL)
      fields->setBitrate(header->vbr_bitrate);
  } 
  
  return fields->getBitrate();
}
int PL_Mp3File::getTrack()const
{
    if((fields->getTrackNumber()==-1)||(mode))
    {

//      if(!linked)
//        link();

      fields->setTrackNumber(Mp3tagger->getValue(TRACK).toInt());

    }
    return fields->getTrackNumber();
}

QStringList* PL_Mp3File::getgenres()
{
  return  Mp3tagger->getgenres();
}
void PL_Mp3File::setTitle(QString p)
{
    fields->setTitle(p);
}
void PL_Mp3File::setArtist(QString p)
{

  fields->setArtistName( p);
}
void PL_Mp3File::setGenre(int p)
{
  fields->setGenre(p);
}
void PL_Mp3File::setYear(int p)
{
  fields->setYear(p);
}
void PL_Mp3File::setAlbumtitle(QString p)
{

  fields->setAlbum(p);
}

void PL_Mp3File::setComment(QString p)
{

  fields->setComment(p);
}
void PL_Mp3File::setTrack(int p)
{
    fields->setTrackNumber(p);

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
const QImage& PL_Mp3File::getPicture()const
{
    if((fields->getImage().isNull())||(mode))
    {

//      if(!linked)
//        link();

     fields->setImage(Mp3tagger->getValue(PICTURE).value<QImage>());

    }
    return fields->getImage();
}

void PL_Mp3File::setValue(DataField x,QVariant& value,bool replace)
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
void PL_Mp3File::readData(QDataStream & in)
{
    /// @warning readData
  //in >> fields;
    qDebug() << "PL_Mp3File::readData";
}
void PL_Mp3File::writting(QDataStream & out) const
{

  out     << fields;

}
void PL_Mp3File::ForceTagReading()
{
  mode=1;
}
void PL_Mp3File::parseHeader()
{
  header = Mp3tagger->GetMp3HeaderInfo();
}


