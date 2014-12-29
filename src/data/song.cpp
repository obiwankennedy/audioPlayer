#include "song.h"

Song::Song()
    : m_genre(-1),m_duration(-1),m_bitrate(-1),m_year(-1)
{

}
// gets
QString Song::getTitle() const
{
    return m_title;
}

QString Song::getArtistName() const
{
    return m_artistName;
}
QString Song::getAlbum() const
{
    return m_album;
}
QString Song::getComment() const
{
    return m_comment;
}
QString Song::getLyrics() const
{
    return m_lyrics;
}

QImage Song::getImage() const
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
int Song::getTracNumber() const
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
void Song::setTracNumber(int i)
{
    m_trackNumber = i;
}
void Song::setDuration(int i)
{
    m_duration = i;
}
