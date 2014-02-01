/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
 *   renaud.guezennec@gmail.com   *
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
#ifndef DEFAULTDECORATOR_H
#define DEFAULTDECORATOR_H

#include "itemdecorator.h"

/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class Defaultdecorator
 * \brief class to manage data access to an default media file.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no             
*/
class PlaylistItem;
class Defaultdecorator : public ItemDecorator
{
  QFileInfo* fi;
public:
    Defaultdecorator();
    Defaultdecorator(PlaylistItem* item);
    virtual ~Defaultdecorator();
   
    
    QVariant getMember(dataColumn x) const;
    virtual void setValue(dataColumn x,QVariant& value,bool replace);
    
    PlaylistItem* getItem()  ;
    virtual void setItem(PlaylistItem* _item);
    QString extractFilename();
    QStringList* getgenres();
    virtual void ForceTagReading();
};

#endif
