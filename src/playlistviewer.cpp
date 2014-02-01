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
#include "playlistviewer.h"
#include "directoryFacade/pl_directoryfacade.h"
#include "tableheaderview.h"


#include <QtWidgets>



PlayListViewer::PlayListViewer(QWidget *p)
 : QTabWidget(p),m_tabList(NULL)
    {

        tablemodel=NULL;
        treemodel=NULL;
        listmodel=NULL;

        previousTabIndex = -1;
        m_tabList = new QList<PL_AbstractListViewer*>;
        m_viewerNotDisplayed = new QList<PL_AbstractListViewer*>;
        setTabsClosable(true);
        connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(onCloseTab(int )));


        visibleColumn = new QList<int>;
        m_widgetList = new QList<QWidget*>;

        myPlaylist = Playlist::getInstance();



        main = new PL_TableView(this);
        listview = new PL_ListView(this);
        mytreeview = new PL_treeview;
        mytreeview->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Expanding );

        main->setHorizontalHeader(new TableHeaderView(main->getMapheader(),Qt::Horizontal,this));



        m_tabList->append(main);
        m_tabList->append(mytreeview);
        m_tabList->append(listview);

        m_widgetList->append(main);
        m_widgetList->append(mytreeview);
        m_widgetList->append(listview);




        former_index = NULL;
        index = NULL;

    for(int i = 0; i< m_tabList->size();i++)
    {
        PL_AbstractListViewer* p = m_tabList->at(i);
        QWidget* wd = m_widgetList->at(i);
        this->addTab(wd,p->tabTitle());
    }

        #ifdef HAVE_PHONON
        
        connect(this,SIGNAL(SetId(int)),main,SLOT(onSelect(int)));
        
        #endif

       

        modelUpdated = true;

        connect(main, SIGNAL(dataChanged()),
                this, SIGNAL(dataChanged()));

        connect(main,SIGNAL(dataModelChanged()),this,SLOT(modelsdataChanged()));

        connect(main, SIGNAL(isPastable(bool)),
                this, SIGNAL(isPastable(bool)));

        connect(main, SIGNAL(isCopiable(bool)),
                this, SIGNAL(isCopiable(bool)));


        connect(main, SIGNAL(isCutable(bool)),
                this, SIGNAL(isCutable(bool)));


        
        connect(main, SIGNAL(Maximum(int)),
                this, SIGNAL(Maximum(int)));
                
        connect(main, SIGNAL(Minimum(int)),
                this, SIGNAL(Minimum(int)));
        connect(main, SIGNAL(valueChanged(int)),
                this, SIGNAL(valueChanged(int)));
        connect(main, SIGNAL(CommandStart()),
                this, SIGNAL(CommandStart()));
                
         connect(main, SIGNAL(done()),
               this, SIGNAL(done()));
                
        connect(this, SIGNAL(currentChanged(int)),
               this, SLOT(onChangedTab(int)));

        connect(main,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(slotdoubleClicked(const QModelIndex &)));

}
void PlayListViewer::initWidget()
{
    tablemodel = new PlayListModel(main->getMapheader(),myPlaylist, this);
    main->setModel(tablemodel);

    treemodel = new PL_TreeModel;
    mytreeview->setModel(treemodel);

    listmodel = new PL_ListModel;
    listview->setModel(listmodel);

    main->updateHeader();

    connect(tablemodel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
            this, SIGNAL(dataChanged()));
}

PlayListViewer::~PlayListViewer()
{
  
}

void PlayListViewer::modelsdataChanged()
{
    modelUpdated = true;
}
void PlayListViewer::writeSettings(QSettings& settings)
{
    foreach(PL_AbstractListViewer* p, *m_tabList)
    {
        p->writeSettings(settings);
    }
}
void PlayListViewer::readSettings(QSettings& settings)
{
    foreach(PL_AbstractListViewer* p, *m_tabList)
    {
        p->readSettings(settings);
    }

   
}

Playlist* PlayListViewer::getmyPlaylist() const
{
  return myPlaylist;
}
void PlayListViewer::LinkModelwithTable()
{

    onChangedTab(currentIndex());

}
void PlayListViewer::onChangedTab( int index )
{

    QWidget* p = widget(index);

    if(previousTabIndex != -1)
    {
        m_tabList->at(previousTabIndex)->aboutToHide();
        m_tabList->at(index)->aboutToShow();

    }

    if(modelUpdated)
    {
        if( NULL!= tablemodel )//check the address
        {
           tablemodel->updateModel();
           modelUpdated =false;
        }
        if(NULL!= treemodel)
        {
            treemodel->updateModel();
            modelUpdated =false;
        }
        if(NULL!= listmodel)
        {
            //listmodel->updateModel();
            modelUpdated =false;
        }
    }
    else  if( NULL!= tablemodel )//check the address
    {
       tablemodel->updateModel();

    }

    previousTabIndex = index;
}
void PlayListViewer::openDir(QString _dir)
{

  QMessageBox msgBox;
 msgBox.setText(tr("Where the insertion must be done."));
 msgBox.setInformativeText("Would you like to insert files at the current selection.?");
 msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
 msgBox.setDefaultButton(QMessageBox::No);
 int ret = msgBox.exec();
 int pos = -1;

switch (ret) {
   case QMessageBox::Yes:
    {
     PL_AbstractListViewer* current = getCurrentView();
     if((current->getSelectedItem()->size()>0))
     {
         //qDebug() << "ok ok ok" ;
        pos = myPlaylist->getmyPlaylist().indexOf(current->getSelectedItem()->at(0));
     }
    }
       break;
   default:
       break;
 }


  PL_directoryFacade tmp(_dir);
  QList<PlaylistItem*>* p = tmp.browseDir();
  tablemodel->append(p,pos);

  
}
QList<headerlistview*>* PlayListViewer::getheaderlist()
{
  return main->getMapheader();
}

PL_AbstractListViewer* PlayListViewer::getCurrentView()
{
  return m_tabList->at(currentIndex ());
}
void  PlayListViewer::cancel()
{
    m_tabList->at(currentIndex())->cancel();
}
void PlayListViewer::InitViewmenu(QMenu* menu)
{

    foreach(PL_AbstractListViewer* p, *m_tabList)
    {
        //p->displayMenu(menu);
        QAction* a = menu->addAction(QString("Show %1").arg(p->tabTitle()));
        connect(a,SIGNAL(triggered()),this,SLOT(onShowTab()));
        a->setCheckable(true);
        if(p->isAvailable())
            a->setChecked(true);
        m_groupViewer.append(a);
    }

    menu->addSeparator();
    foreach(PL_AbstractListViewer* p, *m_tabList)
    {
        p->displayMenu(menu);
    }

}
void PlayListViewer::onShowTab()
{
    QObject* tmp = sender();
    if(tmp == NULL)
        return;


    int pos = m_groupViewer.indexOf(static_cast<QAction*>(tmp),0);//position whatever the status of the widget.
    int index = this->indexOf(m_widgetList->at(pos));//if index == -1  the widget is not displayed.
    if(index >-1)
        this->removeTab(index);
    else
        this->addTab(m_widgetList->at(pos),m_tabList->at(pos)->tabTitle());


}
void  PlayListViewer::onCloseTab(int index)
{

    //m_viewerNotDisplayed->append(m_tabList->takeAt(index));


}
void  PlayListViewer::onAddTab(int index)
{

    m_tabList->append(m_viewerNotDisplayed->takeAt(index));

}
QList<int>* PlayListViewer::getVisibleColumn()
{
  return m_tabList->at(currentIndex ())->getVisibleColumn();
}
    
void PlayListViewer::ShowandSelectRow(int row)
{
  main->ShowandSelectRow(row);
}
void PlayListViewer::reset()
{
  myPlaylist->reset();
  tablemodel->updateModel();
}
void PlayListViewer::addfile(QString& filename)
{
    myPlaylist->addfile(filename);
    onChangedTab(currentIndex());

}
 void PlayListViewer::setImportparser(ImportParser* p)
{
  if(p!=NULL)
  {
	  myPlaylist->insert(p->getResult());
          onChangedTab(currentIndex());
  }
}

void PlayListViewer::slotdoubleClicked(const QModelIndex & _index)
{

	if(former_index!=NULL)
	{
            (*myPlaylist)[former_index->row()]->setReading(false);
		main->update(*(former_index));
	}


	this->index=&_index;
	
	if(this->index!=NULL)
        {
		if(this->former_index==NULL)
			this->former_index = new QModelIndex(*index);
		else
			*(this->former_index)=*(this->index);
	}
		
        emit doubleClicked(_index);

        (*myPlaylist)[_index.row()]->setReading(true);
}
void PlayListViewer::cut()
{
    main->cut();
}
void PlayListViewer::copy()
{
    main->copy();
}
void PlayListViewer::paste()
{
    main->paste();
}
qlonglong PlayListViewer::totalTime()
{
    return myPlaylist->reckOnTime();
}
QTextStream& operator<<(QTextStream& Out, const PlayListViewer& B) 
{ 
  Out << (*B.myPlaylist);
  return Out; 
} 
QTextStream& operator>>(QTextStream& is,PlayListViewer& B)
{
  is>>(*B.myPlaylist);
  B.LinkModelwithTable();
  return is;
}
QDataStream& operator<<(QDataStream& Out, const PlayListViewer& B) 
{ 
  Out << (*B.myPlaylist);
  return Out; 
} 
QDataStream& operator>>(QDataStream& is,PlayListViewer& B)
{
  is>>(*B.myPlaylist);
  B.LinkModelwithTable();
  return is;
}
