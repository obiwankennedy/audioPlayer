#include "oggdecorator.h"
#include <QDebug>
//
OggDecorator::OggDecorator(  ) 
	: ItemDecorator()
{
	// TODO
}
//
QVariant OggDecorator::getMember(DataField x) const
{
  //  qDebug() << "get member ogg";
  PL_OggFile* tmp =(PL_OggFile*) item->getMediaFile();

  if(!tmp->is_linked())
  {
      tmp->link();
  }
  
  if(item==NULL)
    return QVariant();

  switch(x)
  {
    case TITLE:
    {
      return (tmp->getTitle());
    }
    case ARTIST:
      return (tmp->getArtist());
    case TIME:
      return tmp->getDuration();
    case ALBUM:
      return (tmp->getAlbumtitle());
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
void OggDecorator::setValue(DataField x,QVariant& value,bool replace)
{

  PL_OggFile* tmp =(PL_OggFile*) item->getMediaFile();
  tmp->setValue(x,value,replace);

}
QStringList* OggDecorator::getgenres()
{
  return new QStringList;
}
void OggDecorator::setItem(PlaylistItem* _item) 
{
  item = _item;
}
PlaylistItem* OggDecorator::getItem() 
{
  return item;
}
void OggDecorator::ForceTagReading()
{
  return;
}
