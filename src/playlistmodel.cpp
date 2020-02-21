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
    m_playList=NULL;
}

PlayListModel::PlayListModel (QList<headerlistview*>* m,Playlist* _p,QObject * parent )
{   
        m_playList = _p;
        this->parentthis=parent;
}

PlayListModel::~PlayListModel()
{

}

QList<PlaylistItem*> PlayListModel::getmyPlaylist() const
{
  return m_playList->getmyPlaylist();
}


QVariant PlayListModel::headerData ( int section,Qt::Orientation orientation,int role ) const
{
        if ( ( orientation!=Qt::Horizontal ) && ( section>-1 ) && ( role == Qt::DisplayRole ) )
        {
              
                return section+1;
        }
        return QVariant();
}
int PlayListModel::rowCount ( const QModelIndex & /*parent*/ ) const
{
  return m_playList->size();
}
int PlayListModel::columnCount ( const QModelIndex &/* parent*/ ) const
{
  return 9;
}

QVariant PlayListModel::data ( const QModelIndex &index, int role ) const
{
        if ( !index.isValid() )
        {
                return QVariant();
        }
        if ( role == Qt::TextAlignmentRole )
        {
                return int ( Qt::AlignLeft | Qt::AlignVCenter );
        }
        else if ( role == Qt::DisplayRole )
        {
                return getValue ( index.row(),index.column() );
        }
        else if ( role == Qt::BackgroundColorRole)
        {
            if(fileAvailable(index.row()))
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
QVariant PlayListModel::getValue ( int row,int col ) const
{
    if ( ( row>-1 ) && ( row<m_playList->size() ) )
    {
        PlaylistItem* p = m_playList->value(row);

        auto itemDeco = p->getKey();

        return itemDeco->getMember(static_cast<dataColumn>(col));
    }

    return QVariant();

}
bool PlayListModel::fileAvailable(int x)  const
{
    if ( ( x>-1 ) && ( x<m_playList->size() ) )
    {
        PlaylistItem* p = m_playList->value(x);
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
  nb_row=m_playList->size();

}
void PlayListModel::append(QList<PlaylistItem*>* p,int pos)
{
    if(pos==-1)
    {
      beginInsertRows(QModelIndex(), m_playList->size(), m_playList->size()+p->size()-1);
      m_playList->insert(p);
      endInsertRows();
    }
    else
    {
        beginInsertRows(QModelIndex(), m_playList->size(), m_playList->size()+p->size()-1);
        m_playList->insert(pos,p);
        endInsertRows();
    }
}
void PlayListModel::append(PlaylistItem* p)
{
  beginInsertRows(QModelIndex(), m_playList->size(),m_playList->size());
  m_playList->append(p);
    endInsertRows();
}

void PlayListModel::getdownItem(QModelIndex & from,QModelIndex & to)//When the selection goes to the bottom.
{
  m_playList->getdownItem(from.row(),to.row());
  emit dataChanged(from,to);
  
}
void PlayListModel::getupItem(QModelIndex & from,QModelIndex & to)//when the selection goes to the top.
{
  m_playList->getupItem(from.row(),to.row());
  emit dataChanged(to,from);

}
