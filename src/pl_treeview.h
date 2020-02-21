#ifndef PL_TREEVIEW_H
#define PL_TREEVIEW_H
//
#include <QTreeView>
#include "pl_abstractListViewer.h"
//
class PL_treeview : public QTreeView, public PL_AbstractListViewer
{
Q_OBJECT
public:
	PL_treeview();

        bool hasCopyPasteSupport() const ;
        bool isTabVisible() const ;
        virtual void readSettings() ;
        virtual void writeSettings();
        virtual QString tabTitle() const ;
        virtual void displayMenu(QMenu* menu);
        virtual  QList<PlaylistItem*>* getSelectedItem();
        virtual QList<int>* getVisibleColumn();
        virtual void aboutToHide();
        virtual void aboutToShow();
 public slots:
        virtual void cancel();

signals:
    void dataModelChanged();
};
#endif
