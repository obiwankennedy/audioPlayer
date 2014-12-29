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
#include "pl_sortcommand.h"

pl_sortcommand::pl_sortcommand(QList<PlaylistItem*> _myselection,int _start, DataField _criteria,PL_TableView* _tableview)
  : PL_COMMAND(),myselection(_myselection),start(_start),criteria(_criteria),tableview(_tableview)
{
  myPlaylist = Playlist::getInstance();
}


pl_sortcommand::~pl_sortcommand()
{
  
}

void pl_sortcommand::doCommand()
{

    myPlaylist->sort(start,&myselection,a->getColunm(),a->getOrder());
 
}
bool pl_sortcommand::check()
{
	a = new SortDialog(tableview);
  if(a->exec())
  {
  	return true;
  }
  return false;
}
void pl_sortcommand::undo()
{
  foreach(PlaylistItem* a, myselection)
  {
    myPlaylist->removeAt(start);
    myPlaylist->insert(start++,a);
  }
  
}

