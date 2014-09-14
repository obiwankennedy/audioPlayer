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
#include "mediafacade.h"
#include <QTextStream>
#include <mp3decorator.h>
#include <defaultdecorator.h>
#include <oggdecorator.h>
MediaFacade::MediaFacade()
{
  //mp3=new Mp3Decorator;
  //other=new Defaultdecorator;
  mp3factory = FactoryMP3::getInstance();
  oggfactory=FactoryOgg::getInstance();
  otherfactory= factoryOTHER::getInstance();
}


MediaFacade::~MediaFacade()
{
//  delete mp3;
  //delete other;
  delete mp3factory;
  delete oggfactory;
  delete otherfactory;
  singleton = NULL;
}
MediaFacade *MediaFacade::singleton = NULL;

MediaFacade* MediaFacade::getInstance()
{
  if(singleton == NULL)
    singleton = new MediaFacade;
  
  
  
  return singleton;
}
void MediaFacade::verify()
{
  if(mp3factory==NULL)
     mp3factory = FactoryMP3::getInstance();
  if(otherfactory==NULL)
    otherfactory= factoryOTHER::getInstance();
  if(oggfactory==NULL)
  	oggfactory=FactoryOgg::getInstance();
}
PL_MediaFile* MediaFacade::buildaMedia(QString& txt,ItemDecorator*& key,SongFields* fields)
{
  PL_MediaFile* tmp=NULL;
  verify();
  //QTextStream out(stderr,QIODevice::WriteOnly);
 // static int i = 0;
  if(txt.endsWith(".mp3",Qt::CaseInsensitive))
  {
//    tmp=mp3factory->buildMedia(txt,fields);
//    key = new Mp3Decorator;
    tmp=oggfactory->buildMedia(txt,fields);
    key = new OggDecorator;
  }
  else if((txt.endsWith(".ogg",Qt::CaseInsensitive))||((txt.endsWith(".m4a",Qt::CaseInsensitive))) ||((txt.endsWith(".mpc",Qt::CaseInsensitive)))||((txt.endsWith(".oga",Qt::CaseInsensitive)))||((txt.endsWith(".flac",Qt::CaseInsensitive))))
  {
  	//out << ++i << " " <<txt <<endl;
 	tmp=oggfactory->buildMedia(txt,fields);
 	key = new OggDecorator; 	
 }
  else
  {
    tmp=otherfactory->buildMedia(txt,fields);
    key = new Defaultdecorator;
  }
  return tmp;
}

