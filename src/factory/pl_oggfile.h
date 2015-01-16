#ifndef PL_OGGFILE_H
#define PL_OGGFILE_H
//
#include "pl_audiofile.h"
#include <pl_taggerid3.h>
#include <QFile>
#include <QString>

#include <pl_taggerogg.h>
#include "../data.h"
#include "data/song.h"
#define FORCING_MODE 1
#define NORMAL_MODE 0
//
class PL_OggFile : public PL_AudioFile
{
	PL_TaggerOgg* oggtagger;
    //QString* m_uri;
    Song* m_song;
    bool linked;
 //TagLib::FileRef *f
public:
	PL_OggFile();
    PL_OggFile(QString& uri,Song* song);
    int getDuration() const;
    virtual const QString& getTitle() const;
    virtual const QString& getArtist() const;
    int getGenre() const;
    virtual const QString& getAlbumtitle() const;
    virtual const QString& getComment() const;
    int getYear() const;
    int getBitrate() const;
	QStringList* getgenres();
    int getTrack() const;
    virtual const QImage& getPicture() const;



    void setTitle(QString p);
    void setArtist(QString p);
    void setGenre(int p);
    void setAlbumtitle(QString p);
    void setComment(QString p);
    void setYear(int p);
    void setTrack(int p);

    void link();
    bool is_linked();
    void setValue(DataField x,QVariant& value,bool replace);
    void ForceTagReading();
    void parseHeader();
    virtual void readData(QDataStream & in);
    virtual void writting(QDataStream & out) const;
};
#endif
