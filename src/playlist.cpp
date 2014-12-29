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
#include "playlist.h"
#include "visitormediaseeker.h"
#include "thread.h"
#include <QDebug>
Playlist::Playlist()
{
    m_totaltime = 0;
    myPlaylist = new QList<PlaylistItem*>;

}


Playlist::~Playlist()
{
  
}

int Playlist::size()
{
  return myPlaylist->size();
}
void Playlist::append(PlaylistItem* a)
{
  myPlaylist->append(a);

}
qlonglong Playlist::reckOnTime()
{
    bool* conv = new bool;
    foreach(PlaylistItem* a, *myPlaylist)
    {

      int time = a->getKey()->getMember(TIME).toInt(conv);

      if((time !=-1)&&(conv))
        m_totaltime+=time;
    }
    //qDebug() << " fyopitd " <<m_totaltime;
    return m_totaltime;
}
void Playlist::removeAt(int a)
{
  myPlaylist->removeAt(a);
}
PlaylistItem* Playlist::value(int x) const
{
 return myPlaylist->value(x);
}
QList<PlaylistItem*> Playlist::getmyPlaylist() const
{
  return (*myPlaylist);
}
void Playlist::addfile(QString& filename)
{
  PlaylistItem *p = new PlaylistItem;
  p->setURI(filename);
  append(p);
}
void Playlist::sort(int start,QList<PlaylistItem*>* myselection,DataField _criteria,Qt::SortOrder order)
{
  PL_ItemCompare compare;
  compare.x=_criteria;
  compare.order = new bool[2];
  switch(order)
  {
   case Qt::DescendingOrder:
     compare.order[0] = false;
     compare.order[1] = true;
     break;
     case Qt::AscendingOrder:
      compare.order[1] = false;
       compare.order[0] = true;
     break;
    
  }
  qStableSort(myPlaylist->begin()+start,myPlaylist->begin()+start+myselection->size(),compare);
}

QList<PlaylistItem*>* Playlist::getP_myPlaylist() const
{
  return myPlaylist;
}

Playlist* Playlist::getInstance()
{
  if(singleton == NULL)
    singleton = new Playlist;
  
  
  
  return singleton;
}
void Playlist::move(int from,int to)
{
    myPlaylist->move(from,to);

}
void Playlist::kill()
{
        if (NULL != singleton)
        {
                delete singleton;
                singleton = NULL;
        }
}

Playlist *Playlist::singleton = NULL;

void Playlist::getdownItem(int from,int to)//When the selection goes to the bottom.
{
  if((from<myPlaylist->size())&&(from>=0))
  myPlaylist->insert(to,myPlaylist->takeAt(from));
  
}

void Playlist::insert(QList<PlaylistItem*>* os)
{
  *myPlaylist << *os;
  

}
void Playlist::insert(int i,QList<PlaylistItem*>* os)
{
int k = 0;
foreach(PlaylistItem* tmp,*os)
    {

        myPlaylist->insert(i+k,tmp);
        k++;
    }
}
void Playlist::getupItem(int from,int to)//when the selection goes to the top.
{
  if((from<myPlaylist->size())&&(from>=0))
  myPlaylist->insert(to,myPlaylist->takeAt(from));
}
void Playlist::reset()
{
  
  myPlaylist->clear();
}
void Playlist::remove(PlaylistItem* a)
{
  myPlaylist->removeAll(a);
 // delete a;
}
void Playlist::insert(int a,PlaylistItem* b)
{
  myPlaylist->insert(a,b);
} 
int Playlist::item2index(PlaylistItem* b)
{
    return myPlaylist->indexOf(b);
}

QTextStream& operator<<(QTextStream& Out, const Playlist& B) 
{ 
  QListIterator<PlaylistItem*> i((*B.myPlaylist));
   PlaylistItem* p= NULL;
  while(i.hasNext())
  {
        p=  i.next();
        p->buildExt();
       Out << (*p);
  }
  return Out; 
} 
    
    
QTextStream& operator>>(QTextStream& is,Playlist& B)
{
  PlaylistItem* p= new PlaylistItem;
  while(!is.atEnd())
  {
    is>>(*p);
    
    B.append(p);
    p= new PlaylistItem;
  }
  return is;
}
QDataStream& operator<<(QDataStream& Out, const Playlist& B)
{
QListIterator<PlaylistItem*> i((*B.myPlaylist));
 PlaylistItem* p= NULL;

  while(i.hasNext())
  {
        p=  i.next();
        p->buildExt();
       Out << (*p);
  }
  return Out;
}
QDataStream& operator>>(QDataStream& is,Playlist& B)
{
    PlaylistItem* p= new PlaylistItem;
  while(!is.atEnd())
  {
    is>>(*p);

    B.append(p);
    p= new PlaylistItem;
  }
  return is;

}
 PlaylistItem*& Playlist::operator[](int column)  const 
 {

        return (*myPlaylist)[column];

 }

