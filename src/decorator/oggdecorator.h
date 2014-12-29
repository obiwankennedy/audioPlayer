#ifndef OGGDECORATOR_H
#define OGGDECORATOR_H
//
#include <itemdecorator.h>
//
class OggDecorator : public ItemDecorator
{

public:
	OggDecorator();
  virtual QVariant getMember(DataField x) const;
  
  virtual void setItem(PlaylistItem* _item);
  virtual  QStringList* getgenres();
  virtual void setValue(DataField x,QVariant& value,bool replace);
	PlaylistItem* getItem(); 
  virtual void ForceTagReading();
};
#endif
