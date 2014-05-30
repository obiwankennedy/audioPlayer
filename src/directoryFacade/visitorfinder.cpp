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
#include "../directoryFacade/visitorfinder.h"
#include <QDebug>
VisitorFinder::VisitorFinder()
 : VisitorNode()
{
  mypreference = Preference_data::getInstance();
  filters = mypreference->getFilters();
  myPlaylist = new QList<PlaylistItem*>;
}


VisitorFinder::~VisitorFinder()
{
  
}

void VisitorFinder::visitDir(Node* _dir)
{

  Directory* dir=(Directory*)_dir;
  PlaylistItem* pl_item;
  QString* a;
  foreach(QString s, dir->entryList(filters,QDir::Files))
  {
    pl_item = new  PlaylistItem;
    a = new QString;
    (*a)=dir->absoluteFilePath(s);

    if(!a->isEmpty())
    {
        pl_item->setURI(*a);
        a = new QString;
        pl_item->SetExt(*a);
        myPlaylist->append(pl_item);

    }
  }

  Directory* tmp=NULL;
  foreach(QString p,dir->entryList(QDir::Dirs | QDir::NoDotAndDotDot))
  {
    tmp= new Directory(dir->absolutePath()+QDir::separator()+ p);
    tmp->acceptVisitor(this);
  }
}
void VisitorFinder::visitFile(Node* /*f*/)
{
  return;
}
void VisitorFinder::setFilsters(QStringList _filters)
{
  filters = _filters;
}
QList<PlaylistItem*>* VisitorFinder::getItemlist()
{
  return myPlaylist;
}
QStringList* VisitorFinder::getFilter()
{
  return &filters;
}
