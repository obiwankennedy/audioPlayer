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
#include "../document/pl_impldocmodel.h"

PL_ImplDocModel::PL_ImplDocModel()
  :listheader(NULL),dataList(NULL)
{
  
}


PL_ImplDocModel::~PL_ImplDocModel()
{
  
}
int PL_ImplDocModel::getColumnCount()
{
  return listheader->size();
}
int PL_ImplDocModel::rowCount()
{
  return dataList->size();
}
QVariant PL_ImplDocModel::getHeaderData(int i)
{
  return listheader->at(i)->name;
}
QVariant PL_ImplDocModel::getData(int x,int y)
{
  if ( ( x>-1 ) && ( x<dataList->size() ) )
  {
    PlaylistItem* p = dataList->value(x);
                
    
               
    return p->getKey()->getMember(( *listheader )[y]->x);
  }
  return QVariant();
}
void PL_ImplDocModel::setList(const QList<PlaylistItem*>* a)
{
  dataList=a;
}
void PL_ImplDocModel::setHeaderList(const QList<headerlistview*>* a)
{
  listheader=a;
}
const QString PL_ImplDocModel::getUri(int x)
{
  if ( ( x>-1 ) && ( x<dataList->size() ) )
  {
    return dataList->value(x)->getURI();
  }
  return QString();
}
