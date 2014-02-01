#include <QDebug>
#include "pl_treeview.h"
#include "pl_texteditordelegate.h"
//
PL_treeview::PL_treeview(  ) 
	: QTreeView()
{
	this->setItemsExpandable ( true);
	this->setItemDelegate(new pl_texteditordelegate(this));
        m_behaviour = ALWAYSSHOWN;
}
//
bool PL_treeview::hasCopyPasteSupport() const
{
    return false;
}
bool PL_treeview::isTabVisible() const
{
    return isVisible();
}

QString PL_treeview::tabTitle() const
{
    return tr("Tree");
}
void PL_treeview::readSettings(QSettings& settings)
{

}
void PL_treeview::writeSettings(QSettings& settings)
{

}
void PL_treeview::displayMenu(QMenu* menu)
{
    Q_UNUSED(menu);
}
QList<PlaylistItem*>* PL_treeview::getSelectedItem()
{
return new QList<PlaylistItem*>;

}
QList<int>* PL_treeview::getVisibleColumn()
{


return new QList<int>;

}
void PL_treeview::cancel()
{
}
void PL_treeview::aboutToHide()
{

}
void PL_treeview::aboutToShow()
{

}
