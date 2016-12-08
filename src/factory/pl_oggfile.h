#ifndef PL_OGGFILE_H
#define PL_OGGFILE_H
//
#include "pl_audiofile.h"
#include <pl_taggerid3.h>
#include <QFile>
#include <QString>

#include <pl_taggerogg.h>
#include "../data.h"

#define FORCING_MODE 1
#define NORMAL_MODE 0
//
class PL_OggFile : public PL_AudioFile
{
	PL_TaggerOgg* oggtagger;
	QString* uri;
    SongFields* fields;
    bool linked;
 //TagLib::FileRef *f
public:
	PL_OggFile();
	PL_OggFile(QString& uri,SongFields* fields);
	int getDuration();
    QString* getTitle();
    QString* getArtist();
    int getGenre();
    QString* getAlbumtitle();
    QString* getComment();    
    int getYear();   
    int getBitrate();
	QStringList* getgenres();
    int getTrack();
    virtual QImage& getPicture();



    void setTitle(QString p);
    void setArtist(QString p);
    void setGenre(int p);
    void setAlbumtitle(QString p);
    void setComment(QString p);
    void setYear(int p);
    void setTrack(int p);

    void link();
    bool is_linked();
    void setValue(dataColumn x,QVariant& value,bool replace);
    void ForceTagReading();
    void parseHeader();
    virtual void readering(QDataStream & in);
    virtual void writting(QDataStream & out) const;
    void unlink();
};
#endif
