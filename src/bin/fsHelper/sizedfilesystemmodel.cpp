#include "sizedfilesystemmodel.h"

SizedFileSystemModel::SizedFileSystemModel(QObject *parent)
    : QFileSystemModel(parent)
{}

QVariant SizedFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(section == (columnCount()-1) && orientation == Qt::Horizontal)
        return tr("Count");
    return QFileSystemModel::headerData(section, orientation, role);
}

QModelIndex SizedFileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    if(column == (columnCount()-1))
    {
        auto id = QFileSystemModel::index(row, column-1, parent);
        return createIndex(row, column, id.internalPointer());
    }
    else
        return QFileSystemModel::index(row, column, parent);
}

QModelIndex SizedFileSystemModel::parent(const QModelIndex &index) const
{
    if(index.column() == (columnCount()-1))
    {
        return QFileSystemModel::parent(createIndex(index.row(), index.column()-1, index.internalPointer()));
        //return createIndex(row, column, id.internalPointer());
    }
    else
        return QFileSystemModel::parent(index);
}

int SizedFileSystemModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return QFileSystemModel::columnCount(parent) + 1;
}

QVariant SizedFileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    if(index.column() == (columnCount()-1))
    {
        if(role == Qt::DisplayRole)
        {
            auto s = index.siblingAtColumn(0);
            return rowCount(s);
        }

    }
    else
        return QFileSystemModel::data(index, role);


    return {};

}
