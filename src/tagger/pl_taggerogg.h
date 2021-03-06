#ifndef PL_TAGGEROGG_H
#define PL_TAGGEROGG_H
//
#include "pl_taglibfile.h"
#include <taglib/fileref.h>
//
#include <taglib/mpegfile.h>

class PL_TaggerOgg : public PL_TagLibFile
{
public:
    void close();
    PL_TaggerOgg();
    PL_TaggerOgg(QString* _filename);
    virtual ~PL_TaggerOgg();
    virtual QVariant getValue(int i);
    virtual void setValue(dataColumn x,QVariant& value,bool replace);
    QStringList* getgenres();

private:
    TagLib::FileRef* myTaggger;
    TagLib::MPEG::File* myTagggerFileMPG;
    QString* filename;
    static QStringList* listgenre;
};
#endif
