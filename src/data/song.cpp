
#include <QTextStream>

#include "song.h"

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
PL_MediaFile* Song::getMediaFile() const
{
    return m_mediaFile;
}

QDataStream& operator<<(QDataStream& Out, const Song& B)
{


  Out << QString();
  Out << B.getUri();

  Out << (*(B.getMediaFile()));


  return Out;
}

QDataStream& operator>>(QDataStream& is,Song& B)
{
    QString a;
  is >> a;

  QString b;
  is >> b;
  B.setUri(b);


  //B.findmedia();
  //is >> (*B.m_mediaFile);


  return is;


}
