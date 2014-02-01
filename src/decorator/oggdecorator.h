#ifndef OGGDECORATOR_H
#define OGGDECORATOR_H
//
#include <itemdecorator.h>
//
class OggDecorator : public ItemDecorator
{

public:
	OggDecorator();
  virtual QVariant getMember(dataColumn x) const;
  
  virtual void setItem(PlaylistItem* _item);
  virtual  QStringList* getgenres();
  virtual void setValue(dataColumn x,QVariant& value,bool replace);
	PlaylistItem* getItem(); 
  virtual void ForceTagReading();
};
#endif
