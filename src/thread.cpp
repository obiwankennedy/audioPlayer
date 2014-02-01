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
#include "thread.h"

Thread::Thread(QList<PlaylistItem*>* list)
 : QThread()
{
  this->list=list;
  stopped=false;
}


Thread::~Thread()
{
}


void Thread::run()
{




  mutex.lock();
  for (int i = 0; ((i < list->size())&&(!stopped)); ++i) 
  {
    list->at(i)->getKey()->acceptVisitor(visit); 
     
  }
  mutex.unlock();
  
}
void Thread::setVisitor(VisitorMedia* visit)
{
 this->visit=visit; 
}
void Thread::stop()
{
  mutex.lock();
  stopped=true;
  mutex.unlock();
}
