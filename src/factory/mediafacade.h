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
#ifndef MEDIAFACADE_H
#define MEDIAFACADE_H

#include "pl_mediafile.h"
#include "../data.h"
#include <itemdecorator.h>
#include "factorymp3.h"
#include "factoryogg.h"
#include "factoryother.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class MediaFacade
 * \brief This class brings together all class needed to create the appropriate media object.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no          
*/

class ItemDecorator;
class MediaFacade
{
 /* ItemDecorator* mp3;
  ItemDecorator* other;*/
  FactoryMP3* mp3factory;
  FactoryOgg* oggfactory;
  factoryOTHER* otherfactory;
  MediaFacade();
  
public:
    

    ~MediaFacade();
    PL_MediaFile* buildaMedia(QString txt,ItemDecorator*& key,Song* song);
    static MediaFacade* getInstance();
    void verify();
private:   
  static MediaFacade* singleton;
};

#endif
