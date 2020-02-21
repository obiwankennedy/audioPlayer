#include "factoryogg.h"
//
FactoryOgg::FactoryOgg() : FactoryMedia()
{
    // TODO
}
//
FactoryOgg* FactoryOgg::singleton= NULL;

FactoryOgg* FactoryOgg::getInstance()
{
    if(singleton == NULL)
        singleton= new FactoryOgg;

    return singleton;
}
PL_MediaFile* FactoryOgg::buildMedia(QString& uri, SongFields* fields)
{
    PL_OggFile* tmp= new PL_OggFile(uri, fields);

    return tmp;
}
