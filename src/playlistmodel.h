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
#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QApplication>
#include <QAbstractListModel>
#include <QStringList>
#include <QTextStream>
#include "playlist.h"
#include "playlistitem.h"
#include "data.h"

/**
    @author Renaud Guezennec
 * \class PlayListModel
 * \brief Re-implemented model for a QTableView. 
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no        
*/



class PlayListModel : public QAbstractListModel
{
   Q_OBJECT
   Playlist* myPlaylist;
   QList<headerlistview*>* mapheader;
   int nb_row;
   int nb_col;
   QObject * parentthis;
   QVariant getValue(int x,int y) const;

public:
    PlayListModel();
    PlayListModel(QList<headerlistview*>* m,Playlist* _p=NULL,QObject * parent = 0);
    ~PlayListModel();

    void setPlaylistItem(QList<PlaylistItem>* _myPlaylist);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    int columnCount();
    QVariant data(const QModelIndex &parent, int role) const;
    QVariant headerData(int section,Qt::Orientation orientation,int role) const;
  
    void updateModel();
    void append(PlaylistItem* p);
    void append(QList<PlaylistItem*>* p,int pos=-1);
    void getdownItem(QModelIndex & from,QModelIndex & to);//When the selection goes to the bottom.
    void getupItem(QModelIndex & from,QModelIndex & to);//when the selection goes to the top.

    void addColunm(headerlistview* x);
    void removeColunm(headerlistview* x);
    QList<PlaylistItem*> getmyPlaylist() const;
    bool fileAvailable(int x)  const;

};

#endif
