#include "searchmodel.h"
//
SearchModel::SearchModel(QStringList& myPlaylist) : QAbstractListModel()
{
    this->myPlaylist= myPlaylist;
}
//
int SearchModel::rowCount(const QModelIndex& /*parent*/) const
{
    return myPlaylist.size();
}
QVariant SearchModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    return myPlaylist[index.row()];
}
