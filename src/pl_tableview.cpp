/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec                                *
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
#include <QTextStream>
#include <QItemSelection>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>
#include <QScrollBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QSettings>
#include "pl_tableview.h"
#include "cmd_thread.h"


PL_TableView::PL_TableView(QWidget * p)
    : QTableView(p),m_model(NULL)
{
    setAlternatingRowColors(true);
    m_behaviour = ALWAYSSHOWN;
    pluginmanager=NULL;
    status=EMPTY_SELECTION;
    last_column=2;
    current=new QModelIndex();
    myPlaylist = Playlist::getInstance();
    myselection=NULL;
    mystack = new QList<PL_COMMAND*>;
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    currentplayingsong=-1;
    setSelectionBehavior(QAbstractItemView::SelectRows);
    m_stateCopy = false;
    m_stateCut = false;
    m_statePaste = false;
    mapheader   = new QList<headerlistview*>;

    connect(this, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(PopupMenurequested(QPoint)));

    connect(this, SIGNAL(entered( const QModelIndex & )),this, SLOT(moveSelection(const QModelIndex&)));

    connect(this, SIGNAL(pressed( const QModelIndex & )),this, SLOT(onClick(const QModelIndex&)));


    connect(this,SIGNAL(dataChanged()),this,SIGNAL(dataModelChanged()));

    pos = -1;
    toPastPosition = -1;

    modifyTag = new QAction(tr("Modify Tag"), this);
    modifyTag->setStatusTip(tr("Modify Tag of all selected files"));
    connect(modifyTag, SIGNAL(triggered()), this, SLOT(onModify()));


    remove= new QAction(tr("Remove item(s)"), this);
    remove->setStatusTip(tr("remove all selected files"));
    connect(remove, SIGNAL(triggered()), this, SLOT(onRemove()));

    removeFile = new QAction(tr("Remove Item(s) from Hard Disk"), this);
    removeFile->setStatusTip(tr("remove all selected files from hard disk"));
    connect(removeFile, SIGNAL(triggered()), this, SLOT(onremoveFile()));


    Forcerefresh= new QAction(tr("Refresh Tag"), this);
    Forcerefresh->setStatusTip(tr("Force the display of Mp3 Tag"));
    connect(Forcerefresh, SIGNAL(triggered()), this, SLOT(onForce()));

    sortSelection = new QAction(tr("Sort the Selection"), this);
    sortSelection->setStatusTip(tr("Sort the Selection"));
    connect(sortSelection, SIGNAL(triggered()), this, SLOT(OnSort()));


    filenameAsTitle = new QAction(tr("Use the filename for the title"), this);
    filenameAsTitle->setStatusTip(tr("Useful for defining the title of many songs."));
    connect(filenameAsTitle, SIGNAL(triggered()), this, SLOT(onFileNameAsTitle()));

    ForcetitleWriting= new QAction(tr("force the title tag writing"), this);
    ForcetitleWriting->setStatusTip(tr("Put the current title in the title tag"));
    connect(ForcetitleWriting, SIGNAL(triggered()), this, SLOT(OnForceWriting()));

    regexp = new QAction(tr("Regex Wizzard"), this);
    regexp->setStatusTip(tr("Change automatically many song"));
    connect(regexp, SIGNAL(triggered()), this, SLOT(OnRegex()));

    moveSelectionTo = new QAction(tr("Move the selection"), this);
    moveSelectionTo->setStatusTip(tr("Quick Move for long playlist"));
    connect(moveSelectionTo, SIGNAL(triggered()), this, SLOT(onMoveSelection()));


    trackdelegate = new TrackDelegate(TIME,YEAR,BITRATE,GENRE);
    setItemDelegate(trackdelegate);


}


PL_TableView::~PL_TableView()
{

}
QList<headerlistview*>* PL_TableView::getMapheader()
{
    return mapheader;
}
void PL_TableView::mousePressEvent(QMouseEvent * event)
{

    QTableView::mousePressEvent(event);
}

void PL_TableView::mouseReleaseEvent(QMouseEvent * event)
{
    if(status!=MOVE_SELECTION)
    {

        emit isCutable(true);
        emit isCopiable(true);
        m_stateCopy = true;
        m_stateCut = true;

    }

    QTableView::mouseReleaseEvent(event);
}
void PL_TableView::onSelect(int p)
{

    int previousSong=currentplayingsong;
    currentplayingsong=p;

    scrollTo(m_model->index(p,0),QAbstractItemView::PositionAtCenter);
#ifdef HAVE_PHONON
    trackdelegate->setPlayed(p);
#endif



    selectionModel()->setCurrentIndex(m_model->index(currentplayingsong,0), QItemSelectionModel::NoUpdate);
    update(m_model->index(currentplayingsong,0));
    update(m_model->index(previousSong,0));
}
void PL_TableView::mouseDoubleClickEvent(QMouseEvent * event)
{

    this->update(m_model->index(currentplayingsong,0));

    QModelIndex index = indexAt(event->pos());
    emit doubleClicked(index);

    currentplayingsong=index.row();

    selectRow(index.row());


}
void PL_TableView::mouseMoveEvent(QMouseEvent* event)
{


    QModelIndex index = indexAt(event->pos());



    if(currentIndex()!=index)
        status=MOVE_SELECTION;

    if((status==MOVE_SELECTION))
    {




        QItemSelectionModel* a =this->selectionModel();

        
        if((index.isValid())&&(!a->isSelected(index)))
        {

            gotoEndSelection(index);
            (*current)=index;
            scrollTo(*current);

        }
        
    }

    this->setSelectionMode(QAbstractItemView::ContiguousSelection);

}
void PL_TableView::moveSelection(const QModelIndex& index)
{


    QItemSelectionModel* a =this->QAbstractItemView::selectionModel();
    if((index.isValid())&&(a->isSelected(index)))
    {
        status=MOVE_SELECTION;

    }
    else if((index.isValid())&&(!a->isSelected(index)))
    {
        status=ADDED_SELECTION;
    }

}
void PL_TableView::onClick(const QModelIndex& index)
{

    QItemSelectionModel* a = this->QAbstractItemView::selectionModel();
    if((index.isValid())&&(a->isSelected(index)))
    {
        if(*current!=index)
            (*current)=index;

    }

}

QModelIndex PL_TableView::moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
{

    return QTableView::moveCursor(cursorAction, modifiers);
}

void PL_TableView::gotoEndSelection(QModelIndex& index)
{

    if(index.row()<current->row())
    {//get down the item behind the selection

        QItemSelectionModel *p = selectionModel();
        QModelIndex first;
        QModelIndex last;
        if(!p->selectedIndexes().empty())
        {
            first = p->selectedIndexes().takeFirst();
            last = p->selectedIndexes().takeLast();

            if(index.row()+1!=first.row())
            {
                index= first.sibling(first.row()-1,0);
            }
            m_model->getdownItem(index,last);


            p->select(QItemSelection(last.sibling(last.row(),0),last),QItemSelectionModel::Deselect);

            first = first.sibling(first.row()-1,first.column());
            last  = last.sibling(last.row()-1,last.column());

            p->select(QItemSelection(first,last),QItemSelectionModel::Select);
            // showRow(index.row());
        }
    }
    else if(index.row()>current->row())
    {//get up the item in front of selectionindex





        QItemSelectionModel *p = selectionModel();
        QModelIndex first;
        QModelIndex last;
        if(!p->selectedIndexes().empty())
        {
            first = p->selectedIndexes().takeFirst();
            last = p->selectedIndexes().takeLast();
            if(index.row()-1!=last.row())
            {
                index= last.sibling(last.row()+1,0);
            }

            m_model->getupItem(index,first);

            p->select(QItemSelection(first,first.sibling(first.row(),last.column())),QItemSelectionModel::Deselect);


            first = first.sibling(first.row()+1,first.column());
            last  = last .sibling(last.row()+1,last.column());
            p->select(QItemSelection(first,last),QItemSelectionModel::Select);
            // showRow(last.row());
        }
    }
}
void PL_TableView::setModel(PlayListModel* pmodel)
{
    m_model = pmodel;
    QTableView::setModel(m_model);
    initColumns();
}
void PL_TableView::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    return;
}

void  PL_TableView::PopupMenurequested(const QPoint & pos)
{

    if(!pluginmanager)
        pluginmanager = SongPluginManager::instance();
    QMenu menu(this);

    menu.addAction(modifyTag);
    menu.addAction(remove);
    menu.addAction(Forcerefresh);
    menu.addAction(sortSelection);
    menu.addAction(ForcetitleWriting);
    menu.addAction(removeFile);
    menu.addAction(regexp);
    menu.addAction(moveSelectionTo);
    menu.addAction(filenameAsTitle);

    QActionGroup *m_group=new QActionGroup(this);
    pluginmanager->setPopupMenu(&menu,m_group);

    connect(m_group,SIGNAL(triggered(QAction*)),this,SLOT(onPluginListGroup(QAction*)));
    if(!(this->indexAt(pos).isValid()))
    {
        modifyTag->setEnabled(false);
        remove->setEnabled(false);
        Forcerefresh->setEnabled(false);
        ForcetitleWriting->setEnabled(false);
        removeFile->setEnabled(false);
        regexp->setEnabled(false);
        moveSelectionTo->setEnabled(false);
        filenameAsTitle->setEnabled(false);
    }
    else
    {
        modifyTag->setEnabled(true);
        remove->setEnabled(true);
        Forcerefresh->setEnabled(true);
        ForcetitleWriting->setEnabled(true);
        removeFile->setEnabled(true);
        regexp->setEnabled(true);
        moveSelectionTo->setEnabled(true);
        filenameAsTitle->setEnabled(true);
    }
    menu.exec(QCursor::pos());
    delete m_group;

}
void PL_TableView::onModify()
{


    QList<QModelIndex> *myselection= new QList<QModelIndex>;

    (*myselection)= this->selectedIndexes();


    EditTagBox *dialog = new EditTagBox(this,myselection, 9);

    if(dialog->exec())
    {


        AmendTag* myamendtag = new AmendTag(dialog->artistEdit->text(),dialog->cbartist->isChecked(),
                                            dialog->TitleEdit->text(), dialog->cbtitre->isChecked(),
                                            dialog->albumEdit->text(), dialog->cbalbum->isChecked(),
                                            dialog->genreCombobox->currentIndex(),dialog->cbgenre->isChecked(),
                                            dialog->uriTextedit->text(), dialog->uriChanged(),
                                            dialog->commetEdit->text(),dialog->cbcomment->isChecked(),
                                            dialog->lineEdit->text(),dialog->cbYear->isChecked(),true);


        foreach(PlaylistItem* pIndex, (*getSelectedItem()))
        {
            pIndex->getKey()->acceptVisitor(myamendtag);

        }
        emit dataChanged();
        delete myamendtag;
    }
    delete dialog;
}

void PL_TableView::ShowandSelectRow(int row)
{
    clearSelection();
    this->scrollTo(m_model->index(row,0),QAbstractItemView::PositionAtCenter);
    selectRow(row);
}

QList<PlaylistItem*>* PL_TableView::getSelectedItem()
{
    if(myselection==NULL)
        myselection = new QList<PlaylistItem*>;
    else
        myselection->clear();


    QModelIndexList *selectedindexes= new  QModelIndexList;
    *selectedindexes=selectedIndexes();

    if(!selectedindexes->isEmpty())
    {
        start = selectedindexes->at(0).row();
        for(int i = start;i<=selectedindexes->at(selectedindexes->size()-1).row();i++)
        {
            myselection->append(myPlaylist->value(i));
        }
    }
    else
        myselection->clear();


    return myselection;
}
void PL_TableView::onremoveFile()
{
    addinstack(new PL_RemoveFileCommand(*getSelectedItem(),start,this));

}
void PL_TableView::onRemove()
{
    addinstack(new PL_RemoveCommand(*getSelectedItem(),start,this));


}
QList<int>*  PL_TableView::getVisibleColumn()
{
    QList<int>* a = new QList<int>;
    foreach(headerlistview* p,(*mapheader))
    {
        if(p->visible)
            a->append(p->x);
    }

    return a;
}
void PL_TableView::onForce()
{
    int r = QMessageBox::warning(this, tr("Play list generator"),
                                 tr("This operation can taken a long time.\n"
                                    "Do you really want to refresh selected items ?"),
                                 QMessageBox::Yes,QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default);
    if(r == QMessageBox::Yes)
    {
        foreach(PlaylistItem* a, *getSelectedItem())
        {

            a->ForceTagReading();

        }
    }
    m_model->updateModel();
}
void PL_TableView::onMoveSelection()
{
    QInputDialog destDialog;
    destDialog.setIntRange (1,myPlaylist->size());
    destDialog.setInputMode ( QInputDialog::IntInput);

    if(destDialog.exec())
    {
        addinstack(new PL_MoveSelection(*getSelectedItem(),start,this,destDialog.intValue()-1));
    }
}
void  PL_TableView::onFileNameAsTitle()
{
    addinstack(new PL_FilenameAsTitle(*getSelectedItem()));

}
void PL_TableView::addinstack(PL_COMMAND* plcmd)
{
    if(plcmd->check())
    {
        mystack->append(plcmd);

        connect(plcmd,SIGNAL(Maximum(int)),this,SIGNAL( Maximum(int)));
        connect(plcmd,SIGNAL(Minimum(int)),this,SIGNAL(Minimum(int)));
        connect(plcmd,SIGNAL(valueChanged(int)),this,SIGNAL(valueChanged(int)));

        //emit CommandStart();

        cmd_thread* mythread = new cmd_thread(plcmd,false);
        connect(mythread,SIGNAL(finished()),this,SLOT(OnUpdate()));
        // plcmd->doCommand();
        mythread->start();
    }
}
void PL_TableView::OnSort()
{
    addinstack(new pl_sortcommand(*getSelectedItem(),start,TITLE,this));
}
void PL_TableView::OnForceWriting()
{
    addinstack(new pl_titlewritingcommand(*getSelectedItem(),start,TITLE,this));
}
void PL_TableView::OnRegex()
{
    RegexWizzard* regexWizzard= new RegexWizzard;
    regexWizzard->show();
    //addinstack(new pl_regexcommand(*getSelectedItem(),start,TITLE,this));
}
void PL_TableView::update(const QModelIndex & a)
{

    for(int i = 0; i<9;i++)
    {
        QTableView::update(a.sibling(a.row(),i));
    }


}
void PL_TableView::cancel()
{

    if(!mystack->isEmpty())
    {
        plcmd = mystack->takeLast();

        connect(plcmd,SIGNAL(Maximum(int)),this,SIGNAL( Maximum(int)));
        connect(plcmd,SIGNAL(Minimum(int)),this,SIGNAL(Minimum(int)));
        connect(plcmd,SIGNAL(valueChanged(int)),this,SIGNAL(valueChanged(int)));
        cmd_thread* mythread = new cmd_thread(plcmd,true);
        connect(mythread,SIGNAL(finished () ),this,SLOT(OnUpdate()));

        mythread->start();

    }
}
void PL_TableView::cut()
{
    toPaste=*getSelectedItem();
    toPastPosition = start;
    emit isPastable(true);
    m_statePaste = true;
}
void PL_TableView::copy()
{
    toPaste=*getSelectedItem();
    toPastPosition= start;
    emit isPastable(true);
    m_statePaste = true;
}
void PL_TableView::paste()
{
    addinstack(new PL_MoveSelection(toPaste,toPastPosition,this,selectedIndexes().at(0).row()));
    emit isPastable(false);
    m_statePaste = false;
}
void PL_TableView::OnUpdate()
{
    m_model->updateModel();
    emit actiondone(mystack->size());
    emit dataChanged();
    plcmd =NULL;
    emit done();
}
bool PL_TableView::hasCopyPasteSupport() const
{
    return true;
}
bool PL_TableView::isTabVisible() const
{
    return isVisible();
}

QString PL_TableView::tabTitle() const
{
    return tr("Table");
}
void PL_TableView::writeSettings()
{
    QSettings settings("eu.renaudguezennec.www", "audioPlayer");

    settings.beginGroup("TableView");
    settings.setValue("viewduration", viewduration->isChecked());
    settings.setValue("viewartist", viewartist->isChecked());
    settings.setValue("viewtitle", viewtitle->isChecked());
    settings.setValue("viewbitrate", viewbitrate->isChecked());
    settings.setValue("viewYear", viewYear->isChecked());
    settings.setValue("viewAlbum", viewAlbum->isChecked());
    settings.setValue("viewComment", viewComment->isChecked());
    settings.setValue("viewGenre", viewGenre->isChecked());
    settings.endGroup();
}
void PL_TableView::readSettings()
{
    QSettings settings("eu.renaudguezennec.www", "audioPlayer");

    settings.beginGroup("TableView");
    viewduration->setChecked(settings.value("viewduration",true).toBool ()) ;
    viewartist->setChecked(settings.value("viewartist",true).toBool ());
    viewtitle->setChecked(settings.value("viewtitle",true).toBool ());
    viewbitrate->setChecked(settings.value("viewbitrate",false).toBool ());
    viewYear->setChecked(settings.value("viewYear",false).toBool ());
    viewAlbum->setChecked(settings.value("viewAlbum",false).toBool ());
    viewComment->setChecked(settings.value("viewComment",false).toBool ());
    viewGenre->setChecked(settings.value("viewGenre",false).toBool ());

    settings.endGroup();

}
void PL_TableView::aboutToHide()
{
    internalMenu->menuAction()->setVisible (false);
}
void PL_TableView::aboutToShow()
{
    internalMenu->menuAction()->setVisible (true);

    emit isCutable( m_stateCut);
    emit isCopiable(m_stateCopy);
    emit isPastable(m_statePaste);

}
void PL_TableView::displayMenu(QMenu* menu)
{
    internalMenu = menu->addMenu(tr("Visible Columns"));
//enum dataColumn{TITLE,ARTIST,TIME,YEAR,ALBUM,TRACK,GENRE,COMMENT,BITRATE,PICTURE};

    viewbitrate= new QAction(tr("Bitrate"), this);
    viewbitrate->setData(BITRATE);
    viewbitrate->setStatusTip(tr("Add/remove the bitrate column"));
    viewbitrate->setCheckable(true);
    viewbitrate->setChecked(false);


    viewYear= new QAction(tr("Year"), this);
    viewYear->setData(YEAR);
    viewYear->setStatusTip(tr("Add/remove the year column"));
    viewYear->setCheckable(true);
    viewYear->setChecked(false);

    viewComment= new QAction(tr("Comment"), this);
    viewComment->setData(COMMENT);
    viewComment->setStatusTip(tr("Add/remove the comment column"));
    viewComment->setCheckable(true);
    viewComment->setChecked(false);

    viewGenre= new QAction(tr("Genre"), this);
    viewGenre->setData(GENRE);
    viewGenre->setStatusTip(tr("Add/remove the genre column"));
    viewGenre->setCheckable(true);
    viewGenre->setChecked(false);

    viewtrack = new QAction(tr("Track #"), this);
    viewtrack->setData(TRACK);
    viewtrack->setStatusTip(tr("Add/remove the track number column"));
    viewtrack->setCheckable(true);
    viewtrack->setChecked(false);

    viewduration= new QAction(tr("Duration"), this);
    viewduration->setData(TIME);
    viewduration->setStatusTip(tr("Add/remove the genre column"));
    viewduration->setCheckable(true);
    viewduration->setChecked(true);

    viewartist= new QAction(tr("Artist"), this);
    viewartist->setData(ARTIST);
    viewartist->setStatusTip(tr("Add/remove the genre column"));
    viewartist->setCheckable(true);
    viewartist->setChecked(true);


    viewtitle= new QAction(tr("Title"), this);
    viewtitle->setData(TITLE);
    viewtitle->setStatusTip(tr("Add/remove the genre column"));
    viewtitle->setCheckable(true);
    viewtitle->setChecked(true);

    viewAlbum= new QAction(tr("Album Name"), this);
    viewAlbum->setData(ALBUM);
    viewAlbum->setStatusTip(tr("Add/remove the Album Name column"));
    viewAlbum->setCheckable(true);
    viewAlbum->setChecked(false);

    readSettings();

    m_columnList.append(viewbitrate);
    m_columnList.append(viewtitle);
    m_columnList.append(viewAlbum);
    m_columnList.append(viewduration);
    m_columnList.append(viewtrack);
    m_columnList.append(viewGenre);
    m_columnList.append(viewComment);
    m_columnList.append(viewYear);

    internalMenu->addAction(viewtitle);
    internalMenu->addAction(viewartist);
    internalMenu->addAction(viewduration);
    internalMenu->addAction(viewAlbum);
    internalMenu->addAction(viewYear);
    internalMenu->addAction(viewtrack);
    internalMenu->addAction(viewComment);
    internalMenu->addAction(viewGenre);
    internalMenu->addAction(viewbitrate);
    internalMenu->addSeparator();
    menu->addSeparator();

    connect(viewtitle,SIGNAL(triggered()),this,SLOT(addColunm()));
    connect(viewAlbum,SIGNAL(triggered()),this,SLOT(addColunm()));
    connect(viewartist,SIGNAL(triggered()),this,SLOT(addColunm()));
    connect(viewduration,SIGNAL(triggered()),this,SLOT(addColunm()));
    connect(viewbitrate,SIGNAL(triggered()),this,SLOT(addColunm()));
    connect(viewYear,SIGNAL(triggered()),this,SLOT(addColunm()));
    connect(viewComment,SIGNAL(triggered()),this,SLOT(addColunm()));
    connect(viewGenre,SIGNAL(triggered()),this,SLOT(addColunm()));
    connect(viewtrack,SIGNAL(triggered()),this,SLOT(addColunm()));
}

void PL_TableView::initColumns()
{

    for(auto act : m_columnList)
    {
        if(act->isChecked())
        {
            showColumn(act->data().toInt());
        }
        else
        {
            hideColumn(act->data().toInt());
        }
    }

    horizontalHeader()->setSectionResizeMode(TITLE,QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(ARTIST,QHeaderView::Stretch);


}

void PL_TableView::addColunm()
{
    QAction *action = qobject_cast<QAction *>(sender());
    auto col = action->data().toInt();
    if(action->isChecked())
    {
        showColumn(col);
    }
    else
    {
        hideColumn(col);
    }
    writeSettings();
}

void PL_TableView::onPluginListGroup(QAction * action)
{
    //pluginmanager->perform(action,selectionModel());
}

