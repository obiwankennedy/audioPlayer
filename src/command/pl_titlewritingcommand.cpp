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
#include "pl_titlewritingcommand.h"

pl_titlewritingcommand::pl_titlewritingcommand(QList<PlaylistItem*> _myselection,int _start, dataColumn _criteria,PL_TableView* _tableview)
  : PL_COMMAND(),myselection(_myselection),start(_start),criteria(_criteria),tableview(_tableview)
{
  myPlaylist = Playlist::getInstance();
}


pl_titlewritingcommand::~pl_titlewritingcommand()
{
}


void pl_titlewritingcommand::doCommand()
{
 	int step = myselection.size()/100;
  	emit Maximum(100);
  	int i = 0;
  	int k = 0;
  	emit Minimum(i);
  foreach(PlaylistItem* a, myselection)
  {
  	    	if(i>=step)
    	{
		  	emit valueChanged(++k);
		  	i = 0;
	  	}
		    QVariant ab = a->getKey()->getMember(TITLE);
		    a->getKey()->setValue(TITLE,ab,true);
		    i++;
  }
  emit done();
}
void pl_titlewritingcommand::undo()
{
  
}
