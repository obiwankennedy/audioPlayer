#ifndef TABLEHEADERVIEW_H
#define TABLEHEADERVIEW_H

#include <QHeaderView>
#include "data.h"
class TableHeaderView : public QHeaderView
{
public:
    TableHeaderView(QList<headerlistview*>* mapheader,Qt::Orientation orientation, QWidget * parent = 0);

    ResizeMode resizeMode ( int logicalIndex ) const;
    bool isSectionHidden ( int logicalIndex ) const;
private:
 QList<headerlistview*>* mapheader;
};

#endif // TABLEHEADERVIEW_H
