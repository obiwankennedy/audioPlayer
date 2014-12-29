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
#include "pl_taggerid3.h"
#include <id3/tag.h>
#include <id3/misc_support.h>
#include <id3/utils.h>
#include <id3/readers.h>
#include <QTextCodec>
#include <QTextStream>
#include <QDebug>

PL_TaggerID3::PL_TaggerID3()
{
//  initGenreList();
  
 
}
PL_TaggerID3::PL_TaggerID3(QString* _filename)
{
  

  filename=_filename;

  myTaggger = new ID3_Tag;
  myTaggger->Link(filename->toStdString().c_str());


  m_mp3header=NULL;


}

PL_TaggerID3::~PL_TaggerID3()
{
  delete myTaggger;
}

QVariant PL_TaggerID3::getValue(int i)
{
  
  ID3_FrameID id =getIDFrame(i);
  ID3_Frame* myFrame = NULL;
  
  myFrame=myTaggger->Find(id);
  

  if(myFrame!=0) 
  {
    char* tmp= new char[ SIZE_DATA ];
    myFrame->Field(ID3FN_TEXT).Get(tmp,SIZE_DATA);
    return QString(tmp);
  }
  
  return QString();
}
void PL_TaggerID3::setValue(DataField x,QVariant& data,bool replace)
{
  

  bool a;
  
 
  
  switch(x)
  {
    case TITLE:
      ID3_AddTitle(myTaggger,data.toString().toStdString().c_str() ,replace);
      break;
    case ARTIST:
      ID3_AddArtist(myTaggger,data.toString().toStdString().c_str() ,replace);
      break;
    case YEAR:
      ID3_AddYear(myTaggger,data.toString().toStdString().c_str() ,replace);
      break;
    case ALBUM:
      ID3_AddAlbum(myTaggger,data.toString().toStdString().c_str() ,replace);
      break;
    case GENRE:
      ID3_AddGenre(myTaggger,data.toInt(&a),replace);
      break;
    case TRACK:
        ID3_AddTrack(myTaggger,data.toInt(&a),0,replace);
        break;
    case COMMENT:
      ID3_AddComment(myTaggger, data.toString().toStdString().c_str(), data.toString().toStdString().c_str(), replace);
      break;
    case TIME:
    case BITRATE:
      return;
  }
  
  myTaggger->Update();

}


ID3_FrameID PL_TaggerID3::getIDFrame(int i)
{

  switch(i)
  {
    case TITLE:
      return ID3FID_TITLE;
    case ARTIST:
     return ID3FID_LEADARTIST;
    case YEAR:
      return ID3FID_YEAR;
    case TRACK:
      return ID3FID_TRACKNUM;
    case ALBUM:
      return ID3FID_ALBUM;
    case TIME:
      return ID3FID_SONGLEN;
    case GENRE:
      return ID3FID_CONTENTTYPE; 
    case COMMENT: 
      return ID3FID_COMMENT; 
    default:
      return ID3_FrameID();
  }
}


QStringList *PL_TaggerID3::listgenre = NULL;



QStringList* PL_TaggerID3::getgenres()
{
  return listgenre;
}


 const Mp3_Headerinfo* PL_TaggerID3::GetMp3HeaderInfo()
{
  return myTaggger->GetMp3HeaderInfo();
}
