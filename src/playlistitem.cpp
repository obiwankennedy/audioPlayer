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
  :m_uri(NULL),m_ext(NULL),m_mediaFile(NULL)
{
  m_song = new Song;
  facade = MediaFacade::getInstance();
  urichanged = false;
  qRegisterMetaTypeStreamOperators<PlaylistItem>("PlaylistItem");
}

PlaylistItem *PlaylistItem::ms_currentPlayedItem = NULL;

PlaylistItem::~PlaylistItem()
{

  facade = NULL;
  delete m_song;
  delete m_mediaFile;
  delete m_uri;
  delete m_ext;
}

PlaylistItem::PlaylistItem(const PlaylistItem& original)
{
  this->facade = MediaFacade::getInstance();
    this->m_mediaFile = NULL;
  
  m_song = new SongFields;
  *m_song = original.getSong();
//  this->fields->Title = original.fields->Title;
//  this->fields->Artist= original.fields->Artist;
//  this->fields->genre=original.fields->genre;
//  this->fields->album= original.fields-> album;
//  this->fields->duration=original.fields->duration;
//  this->fields->Bitrate=original.fields-> Bitrate;
//  this->fields->Comment =original.fields->Comment;
//  this->fields->Year=original.fields->Year;
//  this->fields->m_image=original.fields->m_image;

    this->m_ext=new QString();
    this->m_uri=new QString();

  if(NULL!=original.m_uri)
  {

    *this-> m_uri=*original.m_uri;
  }

  if(NULL!=original.m_ext)
  {

    *this-> m_ext=*original.m_ext;
  }

  findmedia();

}
//MediaFacade *PlaylistItem::facade = NULL;
QString PlaylistItem::getReadableTitle()
{
	return QString("%1 - %2").arg(this->fields->Artist).arg(this->fields->Title);
}
const QString PlaylistItem::getURI() const
{
  if(NULL!=m_song)
  {
      m_song->getUri();
  }
}
QImage& PlaylistItem::getPicture()
{
    fields->m_image = getKey()->getMember(PICTURE).value<QImage>();

    return fields->m_image;
}

void PlaylistItem::setURI(QString & p) 
{
    if(NULL!=m_song)
    {
        m_song->setUri(p);
        urichanged = true;
        findmedia();
    }
}

void PlaylistItem::findmedia()
{
  if((m_mediaFile==NULL)||(urichanged))
  {
    exploseExt();
    m_mediaFile=facade->buildaMedia(*m_uri,key,fields);
    key->setItem(this);
  }
}
QString PlaylistItem::toString()
{

     
        if((fields->Title.isNull()))
         fields->Title=getKey()->getMember(TITLE).toString();
        if((fields->Artist.isNull()))
          fields->Artist=getKey()->getMember(ARTIST).toString();
        

            
       return QString(fields->Artist+" - "+fields->Title);
	
}
const QString PlaylistItem::getExt() const
{
  if(m_ext==NULL)
    return QString();
  
  return *m_ext;
}
void PlaylistItem::SetExt(QString& p)
{
  m_ext=&p;
  exploseExt();
}


void PlaylistItem::buildExt()
{
  int a;
  
  if(m_ext==NULL)
  { 
    m_ext = new QString;
  }
        if(fields->duration==-1)
           a = 0;
        else
           a=fields->duration;
        a/=1000;
        
        if((fields->Title.isNull()))
         /* *fields->Title=*/getKey()->getMember(TITLE).toString();
        if((fields->Artist.isNull()))
         /* *fields->Artist=*/ getKey()->getMember(ARTIST).toString();
        

            
       (*m_ext) = "#EXTINF:"+QString::number(a)+","+fields->Artist.simplified()+" - "+fields->Title.simplified();
 
  
}
void PlaylistItem::exploseExt()
{
  if((m_ext!=NULL)&&(!m_ext->isEmpty()))
  {
    QStringList a = m_ext->split(':');
    if(a.size()==2)
    {
    a = a[1].split(',');
        if(a.size()==2)
        {
                bool ok;
                int tmptime = a[0].toInt(&ok,10);
                if(ok)
                  fields->duration = (1000*tmptime);
                
                a = a[1].split("- ");
                if(a.size()==2)
                {

                  (fields->Title) = a[1].simplified();

                  (fields->Artist) = a[0].simplified();
                }
        }
    }
  }
  m_ext=NULL;
}
PL_MediaFile* PlaylistItem::getMediaFile()
{
  return m_mediaFile;
}

ItemDecorator* PlaylistItem::getKey() const
{
  return key;
}
const SongFields* PlaylistItem::getFields()
{
    return fields;
}
SongFields* PlaylistItem::getFields2()
{
    return fields;
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
Song* PlaylistItem::getSong()
{
    return m_song;
}

const Song* PlaylistItem::getConstSong()
{
    return m_song;
}

QTextStream& operator<<(QTextStream& Out, const PlaylistItem& B) 
{ 
  

  Out << B.getExt()<< endl;
  Out << B.getURI()<< endl;
  
  return Out; 
}

QTextStream& operator>>(QTextStream& is,PlaylistItem& B)
{
  QString* a = new QString(); 

  B.m_uri = new QString();
  
  (*a)= is.readLine();
  if(!a->startsWith("#EXTINF",Qt::CaseSensitive))
  {
    
    B.m_uri=a;
    B.m_ext = new QString();
  }
  else
  {
    B.m_uri = new QString();
    B.m_ext = a;
    (*B.m_uri)=is.readLine();
  }
  B.findmedia();
  return is;

            
}

QDataStream& operator<<(QDataStream& Out, const PlaylistItem& B) 
{ 


  Out << B.getExt();
  Out << B.getURI();

  Out << (*B.m_mediaFile);
  
  
  return Out; 
}

QDataStream& operator>>(QDataStream& is,PlaylistItem& B)
{
  B.m_ext = new QString;
  B.m_uri = new QString;
  is >>(*B.m_ext);
  is >>(*B.m_uri);

  //qDebug() <<( *B.uri) << endl;
  B.findmedia();
  is >> (*B.m_mediaFile);
  
  
  return is;

            
}
