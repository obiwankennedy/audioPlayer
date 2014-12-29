#include "pl_listview.h"
#include <QMenu>
#include <QMouseEvent>

#include "pl_listmodel.h"

PL_ListView::PL_ListView(QWidget* p)
        : QListView(p)
{
    m_behaviour = ALWAYSSHOWN;
}

 bool PL_ListView::hasCopyPasteSupport() const
{

    return false;
}
 bool PL_ListView::isTabVisible() const
{

  return true;
}
 QString PL_ListView::tabTitle() const
{
    return tr("List");

}
 void PL_ListView::displayMenu(QMenu* menu)
{
    internalMenu = menu->addMenu(tr("Edit visible Fields"));

}
void  PL_ListView::aboutToHide()
{

}
void  PL_ListView::aboutToShow()
{

}

 void PL_ListView::readSettings(QSettings& settings)
{


}
 void PL_ListView::writeSettings(QSettings& settings)
{


}
QList<PlaylistItem*>* PL_ListView::getSelectedItem()
{

    return NULL;
}
QList<int>* PL_ListView::getVisibleColumn()
{
    return NULL;
}
void PL_ListView::cancel()
{


}
void PL_ListView::mouseDoubleClickEvent(QMouseEvent* e)
{
    QModelIndex index = indexAt(e->pos());
    if(index.isValid())
    {
       PlaylistItem* item =  index.data(PL_ListModel::DATA).value<PlaylistItem*>();
       emit playSong(item);
    }
}
