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
#ifndef PL_TAGLIBFILE_H
#define PL_TAGLIBFILE_H

#include<QString>
#include<QVariant>
#include "data.h"

/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_TagLibFile
 * \brief Abstract class used for adapt the PlayListGenerator with an unknown external library. Must inherit from it to allow the use of new library.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no           
*/
class PL_TagLibFile
{
  
public:
   virtual ~PL_TagLibFile();
   virtual QString* getValue(int i)=0;
   virtual void setValue(dataColumn x,QVariant& value,bool replace)=0;

};

#endif