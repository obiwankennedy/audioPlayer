#include "tagmodel.h"

TagModel::TagModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int TagModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_tags.size();
}

QVariant TagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::UserRole+1)
        return m_tags.at(index.row());

    return QVariant();
}

QHash<int, QByteArray> TagModel::roleNames() const
{
    auto res =  QAbstractListModel::roleNames();
    qDebug() << res;
    res.insert(Qt::UserRole+1, "tagName");
    return res;
}
