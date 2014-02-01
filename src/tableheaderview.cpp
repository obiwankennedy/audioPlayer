#include "tableheaderview.h"
#include <QDebug>

TableHeaderView::TableHeaderView(QList<headerlistview*>* mmapheader,Qt::Orientation orientation, QWidget * parent)
        : QHeaderView(orientation,parent),mapheader(mmapheader)
{

    setHighlightSections(false);
    setSectionsClickable(false);
}
QHeaderView::ResizeMode TableHeaderView::resizeMode ( int logicalIndex ) const
{
    //qDebug() << (*mapheader)[logicalIndex]->resize << logicalIndex << (*mapheader)[logicalIndex]->name;
    return (*mapheader)[logicalIndex]->resize;
}
bool TableHeaderView::isSectionHidden ( int logicalIndex ) const
{
  //  qDebug() << (*mapheader)[logicalIndex]->visible << logicalIndex << (*mapheader)[logicalIndex]->name;
   return !(*mapheader)[logicalIndex]->visible;
}
