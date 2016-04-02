#ifndef SONG_H
#define SONG_H

#include <QImage>
#include "media.h"
#include "factory/pl_mediafile.h"
#include "itemdecorator.h"

class MediaFacade;
class Song : public Media
{
public:
    Song();
    Song(const Song& original);

    void findmedia();

    // gets
    const QString& getTitle() const;
    const QString& getArtistName() const;
    const QString& getAlbum() const;
    const QString& getComment() const;
    const QString& getLyrics() const;

    const QImage& getImage() const;
    int getYear() const;
    int getBitrate() const;
    int getGenre() const;
    int getTrackNumber() const;
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
    void setTrackNumber(int) ;
    void setDuration(int) ;

    PL_MediaFile* getMediaFile() const;


    void readData(QDataStream& data);
    void writeData(QDataStream& data);

    friend QDataStream& operator<<(QDataStream& os,const Song&);
    friend QDataStream& operator>>(QDataStream& is,Song&);
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

    PL_MediaFile* m_mediaFile;
    ItemDecorator* key;
    MediaFacade* facade;
    bool urichanged;
};

#endif // SONG_H
