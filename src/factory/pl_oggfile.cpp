#include "pl_oggfile.h"
#include <QFileInfo>
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
	QTextStream out(stderr,QIODevice::WriteOnly);
  if((fields->duration==-1)||(mode))
  {
    
      if(!linked)
        link();

      
      
      
     
      
    QString* a = oggtagger->getValue(TIME);
    
    
    bool ok;
    out << *a << endl;
    fields->duration=a->toInt(&ok,10);
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
  
    fields->Title = *oggtagger->getValue(TITLE);
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
    fields->Artist = *oggtagger->getValue(ARTIST);
  }
  return &fields->Artist;
}
int PL_OggFile::getGenre() 
{
 
  if((fields->genre==-1)||(mode))
  {
   
      if(!linked)
        link();
      
    QString* a = oggtagger->getValue(GENRE);
    
    bool ok;
    
    QRegExp rxlen("(\\d+)");
    int pos = rxlen.indexIn(*a);
    if (pos > -1) {
      *a = rxlen.cap(1); 
      
    }
    fields->genre=a->toInt(&ok,10);
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
    
    fields->album =*oggtagger->getValue(ALBUM);
  }
  return &fields->album;
}
QString* PL_OggFile::getComment() 
{
  if((fields->Comment.isNull())||(mode))
  {
    if(!linked)
      link();
    
    fields->Comment =*oggtagger->getValue(COMMENT);
  }
  return &fields->Comment;
  
}
int PL_OggFile::getYear() 
{
  if((fields->Year==-1)||(mode))
  {
   
    if(!linked)
      link();
      
    QString* a = oggtagger->getValue(YEAR);
    bool ok;
    fields->Year=a->toInt(&ok,10);
    if(!ok)
      fields->Year=-1;
  }
  
  return fields->Year;
}   
int PL_OggFile::getBitrate() 
{
  
  
  if((fields->Bitrate==-1)||(mode))
  {
    if(!linked)
      link();
        
    oggtagger->getValue(BITRATE);
    
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
    break;
  }
  
 
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
