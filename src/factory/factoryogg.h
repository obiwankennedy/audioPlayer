#ifndef FACTORYOGG_H
#define FACTORYOGG_H
//
#include "factorymedia.h"
#include "pl_oggfile.h"
//
class FactoryOgg : public FactoryMedia
{


	FactoryOgg();
	static FactoryOgg* singleton;
public:
     PL_MediaFile* buildMedia(QString& uri,Song* fields);
    static FactoryOgg* getInstance();
};
#endif
