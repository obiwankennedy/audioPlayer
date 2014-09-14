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
#include "playlistmodel.h"
#include "mp3decorator.h"
#include "defaultdecorator.h"
#include <QFile>
#include <QDebug>

PlayListModel::PlayListModel()
                : QAbstractListModel()
{
    myPlaylist=NULL;
    mapheader   = new QList<headerlistview*>;
    this->nb_col=0;
    this->nb_row=0;
}

PlayListModel::PlayListModel (QList<headerlistview*>* m,Playlist* _p,QObject * parent )
{   
        myPlaylist = _p;
        mapheader = m;
        this->nb_col=0;
        this->nb_row=0;
        this->parentthis=parent;
}

PlayListModel::~PlayListModel()
{

}

QList<PlaylistItem*> PlayListModel::getmyPlaylist() const
{
  return myPlaylist->getmyPlaylist();
}


QVariant PlayListModel::headerData ( int section,Qt::Orientation orientation,int role ) const
{
        if ( ( orientation==Qt::Horizontal ) && ( section>-1 ) && ( role == Qt::DisplayRole ) )
        {
           return ( *mapheader ) [section]->name;
        }
        else if ( ( orientation!=Qt::Horizontal ) && ( section>-1 ) && ( role == Qt::DisplayRole ) )
        {
              
                return section+1;
        }
        return QVariant();
}
int PlayListModel::rowCount ( const QModelIndex & /*parent*/ ) const
{
  return myPlaylist->size();
}
int PlayListModel::columnCount ( const QModelIndex &/* parent*/ ) const
{
  return mapheader->size();
}
int PlayListModel::columnCount()
{
  
  return mapheader->size();
}
QVariant PlayListModel::data ( const QModelIndex &parent, int role ) const
{
        if ( !parent.isValid() )
        {
                return QVariant();
        }
        if ( role == Qt::TextAlignmentRole )
        {
                return int ( Qt::AlignLeft | Qt::AlignVCenter );
        }
        else if ( role == Qt::DisplayRole )
        {
                return getValue ( parent.row(),parent.column() );


        }
        else if ( role == Qt::BackgroundColorRole)
        {
            if(fileAvailable(parent.row()))
            {
                return QVariant();
            }
            else
            {
                return QColor(Qt::red);
            }
        }
        return QVariant();
}
QVariant PlayListModel::getValue ( int x,int y ) const
{
    ItemDecorator* a=NULL;
    if ( ( x>-1 ) && ( x<myPlaylist->size() ) )
    {
        PlaylistItem* p = myPlaylist->value(x);

        a = p->getKey();

        return a->getMember(( *mapheader )[y]->x);
    }

    return QVariant();

}
bool PlayListModel::fileAvailable(int x)  const
{
    if ( ( x>-1 ) && ( x<myPlaylist->size() ) )
    {
        PlaylistItem* p = myPlaylist->value(x);
        QFileInfo file(p->getURI());

        if(file.isReadable() && file.isFile() && file.exists())
        {
            return true;
        }
        else
            return false;


    }
}

void PlayListModel::updateModel()
{
      //  reset();

    emit layoutChanged();
  nb_row=myPlaylist->size();

}
void PlayListModel::append(QList<PlaylistItem*>* p,int pos)
{
    if(pos==-1)
    {
      beginInsertRows(QModelIndex(), nb_row, nb_row+p->size()-1);
      myPlaylist->insert(p);
      endInsertRows();
    }
    else
    {
        beginInsertRows(QModelIndex(), pos, pos+p->size()-1);
        myPlaylist->insert(pos,p);
        endInsertRows();
    }
}
void PlayListModel::append(PlaylistItem* p)
{

  myPlaylist->append(p);
  nb_row=myPlaylist->size();

}

void PlayListModel::getdownItem(QModelIndex & from,QModelIndex & to)//When the selection goes to the bottom.
{
  myPlaylist->getdownItem(from.row(),to.row());
  emit dataChanged(from,to);
  
}
void PlayListModel::getupItem(QModelIndex & from,QModelIndex & to)//when the selection goes to the top.
{
  myPlaylist->getupItem(from.row(),to.row());
  emit dataChanged(to,from);

}

void PlayListModel::addColunm(headerlistview* x)
{
   mapheader->append(x);
}
void PlayListModel::removeColunm(headerlistview* x)
{
  mapheader->removeAll(x);  
}
