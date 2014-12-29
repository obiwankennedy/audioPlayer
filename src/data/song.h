#ifndef SONG_H
#define SONG_H

#include <QImage>
#include "media.h"

class Song : public Media
{
public:
    Song();

    // gets
    QString getTitle() const;
    QString getArtistName() const;
    QString getAlbum() const;
    QString getComment() const;
    QString getLyrics() const;

    QImage getImage() const;
    int getYear() const;
    int getBitrate() const;
    int getGenre() const;
    int getTracNumber() const;
    int getDuration() const;


    //sets
    void setTitle(QString);
    void setArtistName(QString) ;
    void setAlbum(QString) ;
    void setComment(QString) ;
    void setLyrics(QString) ;

    void setImage(QImage) ;
    void setYear(int) ;
    void setBitrate(int) ;
    void setGenre(int) ;
    void setTracNumber(int) ;
    void setDuration(int) ;

private:
    QString m_title;
    QString m_artistName;
    QString m_album;
    QString m_comment;
    QString m_lyrics;
    QImage m_image;

    int m_year;
    int m_bitrate;
    int m_genre;
    int m_trackNumber;
    int m_duration;
};

#endif // SONG_H
