#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H
//
#include <QAbstractListModel>
#include "playlistitem.h"

//
class SearchModel : public QAbstractListModel
{
Q_OBJECT
        QStringList myPlaylist;

public:
        SearchModel(QStringList& myPlaylist);
	 int rowCount(const QModelIndex & parent = QModelIndex()) const;
	 QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const; 
	 void searchFilter(QString s);

};
#endif
