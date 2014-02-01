#ifndef PL_LISTMODEL_H
#define PL_LISTMODEL_H

#include <QAbstractListModel>
#include "data.h"
#include "playlist.h"
class PL_ListModel : public QAbstractListModel
{
public:
    PL_ListModel();



    virtual int rowCount ( const QModelIndex & /*parent*/ ) const;
    virtual QVariant data ( const QModelIndex &parent, int role ) const;
private:
    Playlist* m_playList;
};

#endif // PL_LISTMODEL_H
