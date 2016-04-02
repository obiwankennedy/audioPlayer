#include "pl_oggfile.h"
#include <QFileInfo>
#include <QTextStream>

#include <QDebug>

/*PL_OggFile::PL_OggFile(  ) 
	: PL_MediaFile()
{
	// TODO
}*/
//
PL_OggFile::PL_OggFile( QString& uri,Song* fields )
    :  PL_AudioFile(uri),m_song(NULL),oggtagger(NULL)
{
	  mode=NORMAL_MODE;
  linked=false;
  //this->m_uri=&uri;
  this->m_song=fields;
}
int PL_OggFile::getDuration()const
{

  if((m_song->getDuration()==-1)||(mode))
  {
    QVariant tmpDuration = oggtagger->getValue(TIME);  
    m_song->setDuration(tmpDuration.toInt());
  }
  return  m_song->getDuration();
}
const QString& PL_OggFile::getTitle() const
{
  if((m_song->getTitle().isEmpty())||(mode))
  { 
    m_song->setTitle(oggtagger->getValue(TITLE).toString());
  }
  
  if(m_song->getTitle().isEmpty())
  {
    
    QFileInfo a(*this);
    QStringList ab = a.fileName().split(".");
    if (ab.size() > 0) 
    {
      m_song->setTitle(ab[ab.size()-2]);
      
    }
  }
  return m_song->getTitle();
}
const QString& PL_OggFile::getArtist() const
{ 
  if((m_song->getArtistName().isEmpty())||(mode))
  {
    m_song->setArtistName(oggtagger->getValue(ARTIST).toString());
  }
  return m_song->getArtistName();
}
int PL_OggFile::getGenre() const
{
 
  if((m_song->getGenre()==-1)||(mode))
  {

    QString genre = oggtagger->getValue(GENRE).toString();
    
    bool ok;
    
    QRegExp rxlen("(\\d+)");
    int pos = rxlen.indexIn(genre);
    if (pos > -1) {
      genre = rxlen.cap(1);
      
    }
    m_song->setGenre(genre.toInt(&ok,10));
    if(!ok)
    m_song->setGenre(-1);
  }
  return m_song->getGenre();
}

const QString& PL_OggFile::getAlbumtitle() const
{
  if((m_song->getAlbum().isNull())||(mode))
  {
    m_song->setAlbum(oggtagger->getValue(ALBUM).toString());
  }
  return m_song->getAlbum();
}
const QString& PL_OggFile::getComment() const
{
  if((m_song->getComment().isNull())||(mode))
  {   
    m_song->setComment(oggtagger->getValue(COMMENT).toString());
  }
  return m_song->getComment();
  
}
int PL_OggFile::getYear() const
{
  if((m_song->getYear()==-1)||(mode))
  {
     m_song->setYear(oggtagger->getValue(YEAR).toInt());
  }  
  return m_song->getYear();
}   
int PL_OggFile::getBitrate() const
{
  if((m_song->getBitrate()==-1)||(mode))
  {
    m_song->setBitrate(oggtagger->getValue(BITRATE).toInt());
  } 
  return m_song->getBitrate();
}        
QStringList* PL_OggFile::getgenres()
{
  return  oggtagger->getgenres();
}
void PL_OggFile::setTitle(QString p)
{
  m_song->setTitle(p);
}
void PL_OggFile::setArtist(QString p)
{
  m_song->setArtistName(p);
}
void PL_OggFile::setGenre(int p)
{
  m_song->setYear(p);
}
void PL_OggFile::setYear(int p)
{
  m_song->setYear(p);
}
void PL_OggFile::setTrack(int p)
{
     m_song->setTrackNumber(p);
}
int PL_OggFile::getTrack() const
{
    return m_song->getTrackNumber();
}
void PL_OggFile::setAlbumtitle(QString p)
{

  m_song->setAlbum(p);
}

void PL_OggFile::setComment(QString p)
{

  m_song->setComment(p);
}



bool PL_OggFile::is_linked()
{
  
  return linked;
  
}
void PL_OggFile::link()
{
  
  oggtagger = new PL_TaggerOgg(m_song->getUri());
  linked=true;
}

void PL_OggFile::setValue(DataField x,QVariant& value,bool replace)
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
const QImage& PL_OggFile::getPicture() const
{

    if((m_song->getImage().isNull())||(mode))
    {
//      if(!linked)
//        link();

      m_song->setImage(oggtagger->getValue(PICTURE).value<QImage>());

    }

    return m_song->getImage();
}

void PL_OggFile::readData(QDataStream & in)
{
    /// @warning readData
   m_song = new Song();
    in>> *m_song ;
    qDebug() << "readdate ogg";
}
void PL_OggFile::writting(QDataStream & out) const
{
  out << *m_song ;
}
void PL_OggFile::ForceTagReading()
{
  mode=FORCING_MODE;
}
void PL_OggFile::parseHeader()
{
 // header = oggtagger->GetMp3HeaderInfo();
}
