#include "pl_listmodel.h"
#include "itemdecorator.h"

#include "playlistitem.h"

PL_ListModel::PL_ListModel()
{
    m_playList = Playlist::getInstance();

}
int PL_ListModel::rowCount ( const QModelIndex & /*parent*/ ) const
{
        return m_playList->size();
}
QVariant PL_ListModel::data ( const QModelIndex &index, int role ) const
{
    if(role == Qt::DisplayRole)
    {
        m_playList->value(index.row())->buildExt();
       return m_playList->value(index.row())->getExt();
    }
    else if(role == PL_ListModel::DATA)
    {
        QVariant var;
        var.setValue(m_playList->value(index.row()));
        return var;
    }

    return QVariant();
}
