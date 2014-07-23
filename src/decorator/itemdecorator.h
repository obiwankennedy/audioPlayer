/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef ITEMDECORATOR_H
#define ITEMDECORATOR_H
#include <QVariant>
#include <QFileInfo>
#include <QStringList>
#include "playlistitem.h"
#include "data.h"
#include "visitormedia.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class ItemDecorator
 * \brief Abstract class. Make easy the data access.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no         
*/
class VisitorMedia;
class PlaylistItem;
class ItemDecorator
{
protected:
  PlaylistItem* item;
public:
  ItemDecorator();
  ItemDecorator(PlaylistItem* _item);
  virtual ~ItemDecorator() {}
  virtual QVariant getMember(dataColumn x) const=0;
  
  virtual void setItem(PlaylistItem* _item) =0;
  virtual  QStringList* getgenres() = 0;
  virtual void setValue(dataColumn x,QVariant& value,bool replace)=0;
  virtual void acceptVisitor(VisitorMedia* visitor);
  virtual void ForceTagReading()=0;
  virtual PlaylistItem* getItem();
};


#endif
