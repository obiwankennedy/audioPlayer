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
#ifndef PL_TREEMODEL_H
#define PL_TREEMODEL_H
//
#include <QAbstractItemModel>
#include "playlist.h"
#include "pl_treeitem.h" 
//

class PL_TreeModel : public QAbstractItemModel
{
Q_OBJECT
	QList<headerlistview*>* mapheader;

    headerlistview *headerYear;

    headerlistview *headerGenre;
    headerlistview *headerAlbum;

    headerlistview* headerartist;
    headerlistview* headertitle;
    Playlist* myPlaylist;
public:
    PL_TreeModel();
    ~PL_TreeModel();
     QVariant data(const QModelIndex &index, int role) const;
     QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;
     QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
     QModelIndex parent(const QModelIndex &index) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;
     void updateModel();
     Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
     virtual bool hasChildren ( const QModelIndex & parent  ) const;
     bool canFetchMore ( const QModelIndex & parent ) const ;
     virtual void fetchMore ( const QModelIndex & parent ) ;
 private:
     void setupModelData(PL_treeitem *parent);
	void initHeaders();
     PL_treeitem *rootItem;
};


#endif
