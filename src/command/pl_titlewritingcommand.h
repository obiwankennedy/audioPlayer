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
#ifndef PL_TITLEWRITINGCOMMAND_H
#define PL_TITLEWRITINGCOMMAND_H

#include <pl_command.h>
#include "pl_tableview.h"
#include "playlist.h"

/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
*/
class pl_titlewritingcommand : public PL_COMMAND
{
  
  QList<PlaylistItem*>  myselection;
  int start;
  dataColumn criteria;
  PL_TableView* tableview;
  Playlist* myPlaylist;
  
public:
  pl_titlewritingcommand(QList<PlaylistItem*> _myselection,int _start, dataColumn _criteria,PL_TableView* _tableview);

    ~pl_titlewritingcommand();
    virtual void doCommand();
    virtual void undo();
};

#endif
