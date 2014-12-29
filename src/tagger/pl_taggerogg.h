#ifndef PL_TAGGEROGG_H
#define PL_TAGGEROGG_H
//
#include "pl_taglibfile.h"
#include <taglib/fileref.h>
//
#include <taglib/mpegfile.h>

class PL_TaggerOgg : public PL_TagLibFile
{
 TagLib::FileRef* myTaggger;
 TagLib::MPEG::File* myTagggerFileMPG;
 QString* filename;
  static QStringList* listgenre;
public:
	PL_TaggerOgg();
	PL_TaggerOgg(QString* _filename);
   virtual ~PL_TaggerOgg();
   virtual QVariant getValue(int i);
   virtual void setValue(DataField x,QVariant& value,bool replace);
   QStringList* getgenres();
};
#endif
