#ifndef PL_TAGGEROGG_H
#define PL_TAGGEROGG_H
//
#include "pl_taglibfile.h"
#include <taglib/fileref.h>
//
class PL_TaggerOgg : public PL_TagLibFile
{
 TagLib::FileRef* myTaggger;
 QString* filename;
  static QStringList* listgenre;
public:
	PL_TaggerOgg();
	PL_TaggerOgg(QString* _filename);
   virtual ~PL_TaggerOgg();
   virtual QString* getValue(int i);
   virtual void setValue(dataColumn x,QVariant& value,bool replace);
   QStringList* getgenres();
};
#endif
