/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
 *   renaud.guezennec@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef PLAYLISTVIEWER_H
#define PLAYLISTVIEWER_H

#include <QtGui>
#include <QTabWidget>
#include <QTextStream>
#include "playlistmodel.h"
#include "pl_tableview.h"
#include "pl_listview.h"
#include "pl_treeview.h"
#include "pl_treemodel.h"
#include "pl_listmodel.h"
#include "importparser.h"

#define MODEL_UNLINKED 0
#define MODEL_LINKED 1

/**
        \author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PlayListViewer
 * \brief Widget to display all playlist views
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no            
*/
class PlayListViewer : public QTabWidget
{
  Q_OBJECT
    PlayListModel* tablemodel;
    PL_TreeModel* treemodel;
    PL_TableView* main;
    PL_ListView* listview;
    PL_ListModel* listmodel;
    PL_treeview* mytreeview;
    Playlist* myPlaylist;
    int Model_status;
    void LinkModelwithTable();
    int sort_state;
    int previousTabIndex;
    bool modelUpdated;
    
    QList<PL_AbstractListViewer*>* m_tabList;
    QList<PL_AbstractListViewer*>* m_viewerNotDisplayed;
    QList<QWidget*>* m_widgetList;

    QList<int>* visibleColumn;

    const QModelIndex* index;
    QModelIndex* former_index;
    QList<QAction*> m_groupViewer;
signals:
    void dataChanged();
    void Maximum(int M);
    void Minimum(int m);
    void valueChanged(int v);
    void CommandStart();
    void done();
    void doubleClicked(const QModelIndex & index);
    void SetId(int i);
    void isCutable(bool a);
    void isCopiable(bool a);
    void isPastable(bool a);
    void actiondone(int );
	
protected slots:
    void onChangedTab( int index );
    void onCloseTab(int index);
    void onAddTab(int index);
    void onShowTab();
    void modelsdataChanged();

public slots:
	void slotdoubleClicked(const QModelIndex & index);
        void cut();
        void copy();
        void paste();
        void cancel();
public:
    PlayListViewer(QWidget *p);
    Playlist* getmyPlaylist() const;
    ~PlayListViewer();
    void openDir(QString _dir);
    void ShowandSelectRow(int row); 
    void reset();
    PL_AbstractListViewer* getCurrentView();
    QList<PL_AbstractListViewer*>* getListViewer(){return  m_tabList;}
    void InitViewmenu(QMenu* menu);

    void readSettings(QSettings& settings);
    void writeSettings(QSettings& settings);
    QList<int>* getVisibleColumn();

    void addfile(QString& filename);
    void setImportparser(ImportParser* p);
    QList<headerlistview*>* getheaderlist();

    qlonglong totalTime();
    void initWidget();


    friend QTextStream& operator<<(QTextStream& os,const PlayListViewer&);
    friend QTextStream& operator>>(QTextStream& is,PlayListViewer&);
    
    friend QDataStream& operator<<(QDataStream& os,const PlayListViewer&);
    friend QDataStream& operator>>(QDataStream& is,PlayListViewer&);
};

#endif
//      connect(undoaction, SIGNAL(triggered()), mytabs, SLOT(cancel()));
//      connect(mytabs, SIGNAL(actiondone(int )), this, SLOT(enabledUndo(int )));
