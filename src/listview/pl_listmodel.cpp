#include "pl_listmodel.h"
#include "itemdecorator.h"
PL_ListModel::PL_ListModel()
{
    m_playList= Playlist::getInstance();
}
int PL_ListModel::rowCount(const QModelIndex& /*parent*/) const
{
    return m_playList->size();
}
QVariant PL_ListModel::data(const QModelIndex& parent, int role) const
{
    /*    if ( !parent.isValid() )
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
        }*/

    if(role == Qt::DisplayRole)
    {
        // ItemDecorator* a=NULL;
        m_playList->value(parent.row())->buildExt();
        return m_playList->value(parent.row())->getExt();
    }
    return QVariant();
}
