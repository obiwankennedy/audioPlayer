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
#ifndef VISITORFINDER_H
#define VISITORFINDER_H


#include <QList>
#include <QStringList>
#include "visitornode.h"
#include "directory.h"
#include "file.h"
#include "playlistitem.h"
#include "preference_data.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class VisitorFinder
 * \brief Class to the Visitor design pattern. It is a visitor used for seeking files and add them in the list.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo no              
*/
class VisitorFinder : public VisitorNode
{
  QStringList filters;
  QList<PlaylistItem*>* myPlaylist;
  Preference_data* mypreference;
public:
  VisitorFinder();
  virtual ~VisitorFinder();
  void visitDir(Node* dir);
  void visitFile(Node* f);
  void setFilsters(QStringList _fliters);
  
  QList<PlaylistItem*>* getItemlist();
  QStringList* getFilter();
};

#endif
