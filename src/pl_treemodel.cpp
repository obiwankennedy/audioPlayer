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
#include "pl_treemodel.h"
#include <QDebug>
//
PL_TreeModel::PL_TreeModel(  ) 
	: QAbstractItemModel()
{
	mapheader   = new QList<headerlistview*>;
	initHeaders();
        rootItem = new PL_treeitem(NULL);
	
	myPlaylist = Playlist::getInstance();
        //qDebug() <<  myPlaylist->size();
	setupModelData(rootItem);
}

 PL_TreeModel::~PL_TreeModel()
 {
     delete rootItem;
 }

 int PL_TreeModel::columnCount(const QModelIndex &parent) const
 {
	
	 if (parent.isValid())
         return static_cast<PL_treeitem*>(parent.internalPointer())->columnCount();
     else
         return rootItem->columnCount();

 }
bool PL_TreeModel::hasChildren ( const QModelIndex & parent  ) const
{

    PL_treeitem *item = static_cast<PL_treeitem*>(parent.internalPointer());

    if(item ==NULL)
        item=  rootItem ;
    return  item->hasChildren();

}
bool PL_TreeModel::canFetchMore ( const QModelIndex & parent ) const
{

    PL_treeitem *item = static_cast<PL_treeitem*>(parent.internalPointer());

        if(item ==NULL)
        item=  rootItem ;
    return item->canFetchMore();
}
void PL_TreeModel::fetchMore ( const QModelIndex & parent )
{
    PL_treeitem *item = static_cast<PL_treeitem*>(parent.internalPointer());
        if(item ==NULL)
            item=  rootItem ;
    item->fetchMore();
}
 QVariant PL_TreeModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
         return QVariant();

     PL_treeitem *item = static_cast<PL_treeitem*>(index.internalPointer());
     


     return item->data(index.column());
 }

 Qt::ItemFlags PL_TreeModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled;

     return Qt::ItemIsEnabled | Qt::ItemIsEditable;
 }

 QVariant PL_TreeModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return ( *mapheader ) [section]->name;
		
     return QVariant();
 }

 QModelIndex PL_TreeModel::index(int row, int column, const QModelIndex &parent)
             const
 {
     PL_treeitem *parentItem;
	
     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<PL_treeitem*>(parent.internalPointer());



     PL_treeitem *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
 }

 QModelIndex PL_TreeModel::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     PL_treeitem *childItem = static_cast<PL_treeitem*>(index.internalPointer());
     PL_treeitem *parentItem = childItem->parent();

     if (parentItem == rootItem)
         return QModelIndex();

     return createIndex(parentItem->row(), 0, parentItem);
 }

 int PL_TreeModel::rowCount(const QModelIndex &parent) const
 {
     PL_treeitem *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<PL_treeitem*>(parent.internalPointer());

     return parentItem->childCount();
 }
void PL_TreeModel::updateModel()
{
        //reset();
                //rootItem->reset();
                setupModelData(rootItem);
  
    emit layoutChanged();
}
bool PL_TreeModel::setData(const QModelIndex &index,
                           const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        PL_treeitem *Itemtemp = static_cast<PL_treeitem*>(index.internalPointer());
        QVariant ab = value;
        Itemtemp->parent()->removeChild(index.data());//remove the child with the old key.
        Itemtemp->amend(ab,NULL);//amend all child

        Itemtemp->parent()->sort(Itemtemp); //move all children
        removeRow(index.row(),index.parent());//remove the old cell
        //QAbstractItemModel::reset();
        return true;
    }
    return false;
}
void PL_TreeModel::setupModelData(PL_treeitem *parent)
{
        parent->setFetchableItems(myPlaylist->getP_myPlaylist());
}
void PL_TreeModel::initHeaders()
{
  
  headerYear= new headerlistview;
  headerYear->name = tr("Year");
  headerYear->x = YEAR;
  
  
  headerGenre= new headerlistview;
  headerGenre->name = tr("Genre");
  headerGenre->x = GENRE;
  
  headertitle = new headerlistview;
  headertitle->x = TITLE;
  headertitle->name = tr ( "Title" );
        
  headerartist= new headerlistview;
  headerartist->x = ARTIST;
  headerartist->name = tr ( "Artist" );
        
        
  headerAlbum= new headerlistview;
  headerAlbum->x = ALBUM;
  headerAlbum->name = tr( "Album Name" );
  
        
	 mapheader->append(headerartist);
	 mapheader->append(headerAlbum);

	 mapheader->append(headertitle);
  

}

