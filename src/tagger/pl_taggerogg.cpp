#include "pl_taggerogg.h"
#include <QTextStream>
#include <taglib/vorbisfile.h>
#include <taglib/tpropertymap.h>
#include <taglib/tstring.h>
#include <taglib/xiphcomment.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2tag.h>
#include <taglib/tlist.h>

#include <QDebug>
//
PL_TaggerOgg::PL_TaggerOgg(  ) 
	: PL_TagLibFile()
{
	// TODO
}
//

PL_TaggerOgg::PL_TaggerOgg(QString* _filename)
{


  filename=_filename;

  //myTaggger = new TagLib::FileRef(filename->toStdString().c_str());
  myTaggger = new TagLib::FileRef(filename->toLocal8Bit());

  TagLib::PropertyMap map = myTaggger->tag()->properties();
  TagLib::ID3v2::Tag* tag=dynamic_cast<TagLib::ID3v2::Tag*>(myTaggger->tag());

  if(tag!=NULL)
  {
      for(std::list<TagLib::ID3v2::Frame*>::const_iterator iter = tag->frameList().begin(); iter !=  tag->frameList().end();++iter)
      {
          //qDebug()<<  TStringToQString((*iter)->toString());
      }
  }

  for(TagLib::SimplePropertyMap::Iterator iter = map.begin(); iter !=  map.end();++iter)
  {
      //qDebug()<<  TStringToQString((*iter).first) << " - \"" << TStringToQString((*iter).second.toString());
  }


}

PL_TaggerOgg::~PL_TaggerOgg()
{
  delete myTaggger;
}

QString* PL_TaggerOgg::getValue(int i)
{

if(NULL == myTaggger->tag())
{
            return new QString();
}



switch(i)
  {
    case TITLE:
    {
             return new QString(TStringToQString(myTaggger->tag()->title()));
    }
    case ARTIST:
    {

         return  new QString(TStringToQString(myTaggger->tag()->artist ()));

    }
    case YEAR: 
    {

    	QString* tmp = new QString;
    	 tmp->setNum(myTaggger->tag()->year());
    	 return tmp;
   	}
    case ALBUM:
        {

            return  new QString(TStringToQString(myTaggger->tag()->album()));
        }
    case TIME:
    {

    	QString* tmp = new QString;
       tmp->setNum(myTaggger->audioProperties()->length()*1000);
       return tmp;
   	}
    case GENRE:
      return  new QString(TStringToQString(myTaggger->tag()->genre())); 
    case COMMENT:          
      return  new QString(TStringToQString(myTaggger->tag()->comment()));
    case TRACK:
      {

          QString* tmp = new QString;
         tmp->setNum(myTaggger->tag()->track());
         return tmp;
      }

    case BITRATE:
    	return new QString(myTaggger->audioProperties()->bitrate());
    default:
      return new QString("");
  }
  
  return new QString("");
}
void PL_TaggerOgg::setValue(dataColumn x,QVariant& data,bool /*replace*/)
{
if(NULL == myTaggger->tag())
            return ;
  switch(x)
  {
    case TITLE:
      myTaggger->tag()->setTitle(TagLib::String(data.toString().toStdString(),TagLib::String::UTF8));
      break;
    case ARTIST:

      myTaggger->tag()->setArtist(TagLib::String(data.toString().toStdString(),TagLib::String::UTF8));
      break;
    case YEAR:
      myTaggger->tag()->setYear(data.toString().toInt());
      break;
    case ALBUM:
      {
     //   TagLib::Ogg::XiphComment* ab = (TagLib::Ogg::XiphComment*)myTaggger->tag();
       // ab->addField("TITLE",TagLib::String(data.toString().toStdString(),TagLib::String::UTF8));
      myTaggger->tag()->setAlbum(TagLib::String(data.toString().toStdString(),TagLib::String::UTF8));

      break;
    }
    case GENRE:
      myTaggger->tag()->setGenre(TagLib::String(data.toString().toStdString(),TagLib::String::UTF8));
      break;
    case COMMENT:
      myTaggger->tag()->setComment(TagLib::String(data.toString().toStdString(),TagLib::String::UTF8));
      break;
  case TRACK:
      myTaggger->tag()->setTrack(data.toString().toInt());
    case TIME:
    case BITRATE:
      return;
  }
  
	myTaggger->save();


}




QStringList *PL_TaggerOgg::listgenre = NULL;



QStringList* PL_TaggerOgg::getgenres()
{
  return listgenre;
}


/* const Mp3_Headerinfo* PL_TaggerOgg::GetMp3HeaderInfo()
{
  return myTaggger->GetMp3HeaderInfo();   
}*/
