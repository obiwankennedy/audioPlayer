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
#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <QDir>
#include "directoryFacade/visitornode.h"

/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class Directory
 * \brief Used for visitor pattern. Represent a directory.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no              
*/
class Directory : public Node,public QDir
{
public:
    Directory();
    Directory(QString dir);
    
    virtual ~Directory();
   virtual void acceptVisitor(VisitorNode* visitor);
};

#endif
