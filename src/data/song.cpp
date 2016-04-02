#include "song.h"
#include "factory/mediafacade.h"


#include <QTextStream>
Song::Song()
    : m_genre(-1),m_duration(-1),m_bitrate(-1),m_year(-1)
{

}
Song::Song(const Song& original)
{
    m_title = original.getTitle();
    m_artistName = original.getArtistName();
    m_album = original.getAlbum();
    m_comment = original.getComment();
    m_image = original.getImage();
    m_bitrate = original.getBitrate();
    m_genre = original.getGenre();
    m_duration = original.getDuration();
    m_year = original.getDuration();
    m_trackNumber = original.getTrackNumber();
    m_lyrics = original.getLyrics();

    m_uri = original.getUri();


}

// gets
const  QString& Song::getTitle() const
{
    return m_title;
}

const QString& Song::getArtistName() const
{
    return m_artistName;
}
const  QString& Song::getAlbum() const
{
    return m_album;
}
const  QString& Song::getComment() const
{
    return m_comment;
}
const QString& Song::getLyrics() const
{
    return m_lyrics;
}

const QImage& Song::getImage() const
{
    return m_image;
}
int Song::getYear() const
{
    return m_year;
}
int Song::getBitrate() const
{
    return  m_bitrate;
}
int Song::getGenre() const
{
    return m_genre;
}
int Song::getTrackNumber() const
{
    return m_trackNumber;
}
int Song::getDuration() const
{
    return m_duration;
}


//sets
void Song::setTitle(QString s)
{
    m_title=s;
}
void Song::setArtistName(QString s)
{
    m_artistName=s;
}
void Song::setAlbum(QString s)
{
    m_album =s;
}
void Song::setComment(QString s)
{
    m_comment = s;
}
void Song::setLyrics(QString s)
{
    m_lyrics = s;
}

void Song::setImage(QImage i)
{
    m_image = i;
}
void Song::setYear(int i)
{
    m_year = i;
}
void Song::setBitrate(int i)
{
    m_bitrate = i;
}
void Song::setGenre(int i)
{
    m_genre = i;
}
void Song::setTrackNumber(int i)
{
    m_trackNumber = i;
}
void Song::setDuration(int i)
{
    m_duration = i;
}

QTextStream& operator<<(QTextStream& Out, const Song& B)
{


  Out << B.getUri()<< endl;


  return Out;
}

QTextStream& operator>>(QTextStream& is, Song& B)
{
  QString a;



  a= is.readLine();
  if(!a.startsWith("#EXTINF",Qt::CaseSensitive))
  {
    B.setUri(a);
  }
  else
  {
    B.setUri(is.readLine());
  }
  return is;


}
void Song::findmedia()
{
    if((m_mediaFile==NULL))
    {
        m_mediaFile=facade->buildaMedia(m_song.getUri(),key,&m_song);
    }
}
PL_MediaFile* Song::getMediaFile() const
{
    return m_mediaFile;
}

QDataStream& operator<<(QDataStream& Out, const Song& B)
{
  Out << QString();
  Out << B.getUri();
  return Out;
}

QDataStream& operator>>(QDataStream& is,Song& B)
{
  QString a;
  is >> a;

  QString b;
  is >> b;
  B.setUri(b);
  return is;


}
void Song::readData(QDataStream& data)
{
    data >> m_uri;
}

void Song::writeData(QDataStream& data)
{
    data << m_uri;
}
QVariant Song::getMember(DataField x) const
{
  switch(x)
  {
    case TITLE:
    {
      return (getTitle());
    }
    case ARTIST:
      return (getArtist());
    case TIME:
      return getDuration();
    case ALBUM:
      return (getAlbumtitle());
    case GENRE:
      return getGenre();
    case TRACK:
      return getTrack();
  case PICTURE:
      return getPicture();
    case COMMENT:
      return getComment();
    case YEAR:
      return getYear();
    case BITRATE:
      return getBitrate();

  }
  return QVariant();



}
void Song::setValue(DataField x,QVariant& value,bool replace)
{

    switch(x)
    {
      case TITLE:
      {
        setTitle(value.toString());
        break;
      }
      case ARTIST:
        setArtistName(value.toString());
        break;
      case TIME:
        break;
      case ALBUM:
        setAlbum(value.toString());
        break;
      case GENRE:
        setGenre(value.toInt());
        break;
      case TRACK:
        setTrackNumber(value.toInt());
        break;
    case PICTURE:
        break;
      case COMMENT:
        setComment(value.toString());
          break;
      case YEAR:
        setYear(value.toInt());
          break;
      case BITRATE:
        setBitrate(value.toInt());
          break;

    }
  tmp->setValue(x,value,replace);

}
