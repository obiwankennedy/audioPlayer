#include "oggdecorator.h"
#include <QDebug>
//
OggDecorator::OggDecorator() : ItemDecorator()
{
    // TODO
}
//
QVariant OggDecorator::getMember(dataColumn x) const
{
    PL_OggFile* tmp= (PL_OggFile*)item->getMediaFile();

    if(item == NULL)
        return QVariant();

    switch(x)
    {
    case TITLE:
    {
        return (*tmp->getTitle());
    }
    case ARTIST:
        return (*tmp->getArtist());
    case TIME:
        return tmp->getDuration();
    case ALBUM:
        return (*tmp->getAlbumtitle());
    case GENRE:
        return tmp->getGenre();
    case TRACK:
        return tmp->getTrack();
    case PICTURE:
        return tmp->getPicture();
    case COMMENT:
    case YEAR:
    case BITRATE:
        return QVariant();
    }
    return QVariant();
}
void OggDecorator::setValue(dataColumn x, QVariant& value, bool replace)
{
    PL_OggFile* tmp= (PL_OggFile*)item->getMediaFile();
    tmp->setValue(x, value, replace);
}
QStringList* OggDecorator::getgenres()
{
    return new QStringList;
}
void OggDecorator::setItem(PlaylistItem* _item)
{
    item= _item;
}
PlaylistItem* OggDecorator::getItem()
{
    return item;
}
void OggDecorator::ForceTagReading()
{
    return;
}
