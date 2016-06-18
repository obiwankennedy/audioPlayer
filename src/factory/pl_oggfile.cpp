#include "pl_oggfile.h"
#include <QFileInfo>
#include <QDebug>

#include <QTextStream>
/*PL_OggFile::PL_OggFile(  ) 
	: PL_MediaFile()
{
	// TODO
}*/
//
PL_OggFile::PL_OggFile( QString& uri,SongFields* fields ) 
	:  PL_AudioFile(uri),fields(NULL)
{
	  mode=NORMAL_MODE;
  linked=false;
  this->uri=&uri;
  this->fields=fields;
  //header=NULL;
}
int PL_OggFile::getDuration()
{
  if((fields->duration==-1)||(mode))
  {
    
      if(!linked)
      {
        link();
     }
     
      
    QVariant tmpDuration = oggtagger->getValue(TIME);    
    bool ok;
    fields->duration=tmpDuration.toInt(&ok);
    if(!ok)
    {
      fields->duration=-1;   
      //fields->duration=(header->time*1000);
    }
        
  }

  return  fields->duration;
}
QString* PL_OggFile::getTitle() 
{

  if((fields->Title.isNull())||(mode))
  {
    if(!linked)
      link();
  
    fields->Title = oggtagger->getValue(TITLE).toString();
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
QString* PL_OggFile::getArtist()
{ 
  if((fields->Artist.isNull())||(mode))
  {
    if(!linked)
      link();
    fields->Artist = oggtagger->getValue(ARTIST).toString();
  }
  return &fields->Artist;
}
int PL_OggFile::getGenre() 
{
 
  if((fields->genre==-1)||(mode))
  {
   
      if(!linked)
        link();
      
    QString genre = oggtagger->getValue(GENRE).toString();
    
    bool ok;
    
    QRegExp rxlen("(\\d+)");
    int pos = rxlen.indexIn(genre);
    if (pos > -1) {
      genre = rxlen.cap(1);
      
    }
    fields->genre=genre.toInt(&ok,10);
    if(!ok)
    fields->genre=-1;
  }
  return fields->genre;
}

QString* PL_OggFile::getAlbumtitle() 
{
  if((fields->album.isNull())||(mode))
  {
    if(!linked)
      link();
    
    fields->album =oggtagger->getValue(ALBUM).toString();
  }
  return &fields->album;
}
QString* PL_OggFile::getComment() 
{
  if((fields->Comment.isNull())||(mode))
  {
    if(!linked)
      link();
    
    fields->Comment =oggtagger->getValue(COMMENT).toString();
  }
  return &fields->Comment;
  
}
int PL_OggFile::getYear() 
{
  if((fields->Year==-1)||(mode))
  {
   
    if(!linked)
      link();
      
     fields->Year = oggtagger->getValue(YEAR).toInt();

  }
  
  return fields->Year;
}   
int PL_OggFile::getBitrate() 
{
  
  
  if((fields->Bitrate==-1)||(mode))
  {
    if(!linked)
      link();
        
    fields->Bitrate = oggtagger->getValue(BITRATE).toInt();
    
  } 
  
  return fields->Bitrate;
}        
QStringList* PL_OggFile::getgenres()
{
  return  oggtagger->getgenres();
}
void PL_OggFile::setTitle(QString p)
{

  (fields->Title) = p;
}
void PL_OggFile::setArtist(QString p)
{

  fields->Artist = p;
}
void PL_OggFile::setGenre(int p)
{
  fields->genre = p;
}
void PL_OggFile::setYear(int p)
{
  fields->Year = p;
}
void PL_OggFile::setTrack(int p)
{
     fields->track=p;
}
int PL_OggFile::getTrack()
{
return fields->track;
}
void PL_OggFile::setAlbumtitle(QString p)
{

  fields->album = p;
}

void PL_OggFile::setComment(QString p)
{

  fields->Comment = p;
}



bool PL_OggFile::is_linked()
{
  
  return linked;
  
}
void PL_OggFile::link()
{
  
  oggtagger = new PL_TaggerOgg(uri);
  linked=true;
}

void PL_OggFile::setValue(dataColumn x,QVariant& value,bool replace)
{
  if(!linked)
    link();
  oggtagger->setValue(x,value,replace);
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
QImage& PL_OggFile::getPicture()
{

    if((fields->Bitrate==-1)||(mode))
    {
      if(!linked)
        link();

      fields->m_image = oggtagger->getValue(PICTURE).value<QImage>();

    }

    return fields->m_image;
}

void PL_OggFile::readering(QDataStream & in)
{
  
  
  

  in >> (fields->Title) ;
  in >> (fields->Artist) ;
  in >> (fields->duration) ;
  in >> (fields->Year) ;
  in >> (fields->genre) ;
  in >> (fields->album);
  in >> (fields->Comment);
  in>> (fields->Bitrate) ;
  in>> (fields->lyrics) ;
}
void PL_OggFile::writting(QDataStream & out) const
{

  out << (fields->Title.simplified())
          << (fields->Artist.simplified())
          << (fields->duration)
          << (fields->Year)
          << (fields->genre)
          << (fields->album.simplified())
          <<(fields->Comment.simplified())
          << (fields->Bitrate)
          << (fields->lyrics.simplified()) ;
}
void PL_OggFile::ForceTagReading()
{
  mode=FORCING_MODE;
}
void PL_OggFile::parseHeader()
{
 // header = oggtagger->GetMp3HeaderInfo();
}
