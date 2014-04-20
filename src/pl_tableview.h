/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec                                *
 *   renaud.guezennec@gmail.com                                            *
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
#ifndef PL_TABLEVIEW_H
#define PL_TABLEVIEW_H

#include <QTableView>

#include "playlistmodel.h"
#include "edittagbox.h"

#include "data.h"
#include "pl_removecommand.h"
#include "pl_removefilecommand.h"
#include "pl_filenameastitle.h"
#include "pl_sortcommand.h"
#include "pl_titlewritingcommand.h"
#include "pl_moveselection.h"
#include "regexwizzard.h"
#include "pl_abstractListViewer.h"
#include "deleguate/trackdelegate.h"
#include "songpluginmanager.h"

/**
 * \author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_TableView
 * \brief Display all playlist items in a table, and allow some statement as modify the order, sorting, deleting. 
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo Change the selection management, it should be done in the setselection and using the mouse event is no longer needed.
*/
class PL_TableView : public QTableView, public PL_AbstractListViewer
{
    Q_OBJECT
public:
  PL_TableView(QWidget * p=0);

    ~PL_TableView();
    void setModel(PlayListModel* m_model);

    void ShowandSelectRow(int row);
    void SynchronizeActionAndColunm();

    bool hasCopyPasteSupport() const ;
    bool isTabVisible() const ;
    void displayMenu(QMenu* menu);
    QString tabTitle() const ;
    void readSettings(QSettings& settings);
    void writeSettings(QSettings& settings);
    void initHeaders();
    QList<headerlistview*>* getMapheader();
    virtual QList<PlaylistItem*>* getSelectedItem();
    virtual QList<int>* getVisibleColumn();
    virtual void aboutToHide();
    virtual void aboutToShow();

    void updateHeader();
//    virtual void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags flags );
protected:
  void mousePressEvent(QMouseEvent * event);
  void mouseReleaseEvent(QMouseEvent * event);
  void mouseDoubleClickEvent(QMouseEvent * event);
  void mouseMoveEvent( QMouseEvent * event );
  bool event(QEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);
  QModelIndex moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers );



public slots:
    void moveSelection(const QModelIndex& index);
    void onClick(const QModelIndex& index);
    void PopupMenurequested(const QPoint & pos);
    void onModify();
    void onRemove();
    void update(const QModelIndex & a);
    void onForce();
    void OnSort();
    virtual void cancel();
    void OnForceWriting();
    void OnUpdate();
    void onSelect(int p);
    void onremoveFile();
    void OnRegex();
    void onMoveSelection();
    void cut();
    void copy();
    void paste();
    void onFileNameAsTitle();
    void onPluginListGroup(QAction * action);

signals:
    void actiondone(int a);
    void dataChanged();
    void Maximum(int M);
    void Minimum(int m);
    void valueChanged(int v);
    void CommandStart();
    void done();
    void isCutable(bool a);
    void isCopiable(bool a);
    void isPastable(bool a);
    void dataModelChanged();
private slots:
    void addColunm();

private:
  void gotoEndSelection(QModelIndex& index);
  void addinstack(PL_COMMAND* plcmd);


    PL_COMMAND* plcmd;
    TrackDelegate* trackdelegate;
    int currentplayingsong;
    int status;
    int last_column;
    QModelIndex* current;

    PlayListModel* m_model;
    QList<headerlistview*>* mapheader;
    QList<PlaylistItem*>*  myselection;
    int start;
    Playlist* myPlaylist;
    QList<PL_COMMAND*>* mystack;
    int pos;
    QList<PlaylistItem*>  toPaste;
    int toPastPosition;
    
    QAction *modifyTag;
    QAction *remove;
    QAction *sortSelection;
    QAction *Forcerefresh;
    QAction *ForcetitleWriting;
    QAction *removeFile;
    QAction *regexp;
    QAction *moveSelectionTo;
    QAction *filenameAsTitle;

    QAction *viewbitrate;
    QAction *viewYear;
    QAction *viewComment;
    QAction *viewGenre;
    QAction *viewAlbum;
    QAction *viewduration;
    QAction *viewartist;
    QAction *viewtitle;
    QAction *viewtrack;


    headerlistview *headerbitrate;
    headerlistview *headerYear;
    headerlistview *headerComment;
    headerlistview *headerGenre;
    headerlistview *headerAlbum;
    headerlistview* headerduration;
    headerlistview* headerartist;
    headerlistview* headertitle;
    headerlistview* headertrack;

    SongPluginManager* pluginmanager;
};

#endif
