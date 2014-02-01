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



#include "playlistgenerator.h"
#include <QTextEdit>
#include <QTextStream>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDebug>
#include <QDockWidget>
#include <QMutableStringListIterator>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>

#include <QtWidgets>

#include "document/pl_impldocmodel.h"
#include "plsimport.h"
#include "xmlimport.h"
#include "pl_databasemanager.h"

#include "dbus/dbusServer.h"

//#include "manhattanstyle.h"
PlayListGenerator::PlayListGenerator()
{



    mysearch = NULL;
    m_database = new PL_DataBaseManager;
    tree = new QTreeView(this);

    model = new QDirModel;

    tree->setModel(model);//tree of directory
    QIcon a(":/pixmaps/icon2.png");
    setWindowIcon ( a );

    setStatusBar(NULL);
    mytabs = new PlayListViewer(this);
    mywizzard= NULL;

    tree->setContextMenuPolicy (Qt::CustomContextMenu);
    setContextMenuPolicy (Qt::CustomContextMenu);

    pluginmanager = SongPluginManager::instance(this);

    m_treedock = new QDockWidget(tr("tree"),this);
    //out  << "test constructor 0" << endl;
    m_treedock->setWidget(tree);

    m_treedock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea,m_treedock);

    workinprogress = new QProgressBar;
    Progressdock = new QDockWidget(tr("Progress bar"));
    Progressdock->setWidget(workinprogress);
    Progressdock->setAllowedAreas(Qt::BottomDockWidgetArea);

    connect(mytabs, SIGNAL(Maximum(int)),workinprogress, SLOT(setMaximum(int)));

    connect(mytabs, SIGNAL(Minimum(int)),workinprogress, SLOT(setMinimum(int)));
    connect(mytabs, SIGNAL(valueChanged(int)),workinprogress, SLOT(setValue(int)));
    connect(mytabs,SIGNAL(CommandStart()),this,SLOT(addDockProgressbar()));
    connect(mytabs,SIGNAL(done()),this,SLOT(removeDockProgress()));







    setCurrentFile("");
    setCentralWidget(mytabs);


    createActions();

    createMenus();

    createToolBars();

    createStatusBar();
     

     //After the preference reading************************************************
     #ifdef HAVE_PHONON

    myplayer = new Player();
    new DbusAdaptorServer(myplayer);
    QDBusConnection connection = QDBusConnection::sessionBus();
    bool rel = connection.registerService("eu.renaudguezennec");
    rel = connection.registerObject("/",myplayer);

    playerdock = new QDockWidget(tr("Music Player"));
    playerdock->setWidget(myplayer);
    playerdock->setAllowedAreas(Qt::TopDockWidgetArea);
    connect(myplayer,SIGNAL(SetId(int)),mytabs,SIGNAL(SetId(int)));
    addDockWidget(Qt::TopDockWidgetArea,playerdock);
    connect(myplayer,SIGNAL(playingSongChanged(SongFields*)),pluginmanager,SLOT(playingSongChanged(SongFields*)));
    connect(myplayer,SIGNAL(playingStop()),pluginmanager,SLOT(playingStopped()));
    #endif


    //m_database->readList();
    //setCurrentFile("/home/renaud/playlist4.qpl");
    mypreferences =  Preference_data::getInstance();

    readSettings();
    pluginmanager->setDock();
    mytabs->initWidget();


    #ifdef HAVE_PHONON
    connect(mytabs,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(addDockplayer(const QModelIndex &)));
    #endif
    tree->setRootIndex(model->index(mypreferences->getUri_default()));
    initializeAssistant();


    connect(mytabs, SIGNAL(dataChanged()),this, SLOT(documentWasModified()));
    connect(tree, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(PopupMenurequested(QPoint)));
    addDockWidget(Qt::BottomDockWidgetArea,Progressdock);
    Progressdock->hide();
    #ifdef HAVE_PHONON

    mySearchFilter = new Search_DialogImpl(this);
    connect(mySearchFilter,SIGNAL(doubleClicked(const QModelIndex &)),mytabs,SIGNAL(doubleClicked(const QModelIndex &)));
    connect(mySearchFilter,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(hideFindingAssist()));
    #endif

    refreshPlugin();

}

void PlayListGenerator::closeEvent(QCloseEvent *event)
{
      if (maybeSave()) {
          closeApplication();
            writeSettings();
            event->accept();
            QApplication::exit();

      } else {
            event->ignore();
      }
}
void PlayListGenerator::closeApplication()
{
#ifdef HAVE_PHONON

    if(NULL!=myplayer)
    {
        myplayer->stopAndClear();
    }

#endif

}


void PlayListGenerator::refreshPlugin()
{
    pluginmanager->displayPreviousState();
}

void PlayListGenerator::newFile()
{
      if (maybeSave()) {
            mytabs->reset();
            setCurrentFile("");
      }
}

void PlayListGenerator::open()
{
      if (maybeSave())
    {
        mytabs->reset();
        setCurrentFile("");
        QString fileName = QFileDialog::getOpenFileName(this,tr("Play List Generator"),".",tr(
            "Supported files (*.m3u *.qpl)\nM3U playList files (*.m3u)\nBinary playList files (*.qpl)"));
            if (!fileName.isEmpty())
            loadFile(fileName);
      }
}
void PlayListGenerator::open2()
{
  
  loadFile(curDir);
  
}
void PlayListGenerator::addDir()
{
  //curDir = QFileDialog::getExistingDirectory(this);


  QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
   dialog.setOptions ( QFileDialog::ShowDirsOnly);

   if(dialog.exec())
   {
          curDir =  dialog.selectedFiles().first();
          openDir();
   }
}
bool PlayListGenerator::save()
{
   // if(m_database->isConnected())
   //     m_database->WriteList();
  if ((curFile.isEmpty())||(!QFile::exists(curFile)))
  {
            return saveAs();
  } else {
            return saveFile(curFile);
  }
}

bool PlayListGenerator::saveAs()
{
  QString fileName = QFileDialog::getSaveFileName(this,tr("Play List Generator"),".",tr("Supported files (*.m3u *.qpl)\nM3U playList files (*.m3u)\nBinary playList files (*.qpl)"));
      if (fileName.isEmpty())
            return false;

      return saveFile(fileName);
}


void PlayListGenerator::about()
{
      QMessageBox::about(this, tr("About PlaylistGenerator"),
                 tr(" <b>PlaylistGenerator</b> is an application to create and to manage "
                  "a MP3 playlist, writen by Renaud GUEZENNEC in C++ using Qt4 and Design Patterns  "
                  "This application is the main year project of the author for "
                     "Dundalk Institute of Technology, 2007-2008, Ireland."));
      

}

void PlayListGenerator::documentWasModified()
{
      setWindowModified(true);
      //modified=true;
}

void PlayListGenerator::createActions()
{
  newAct = new QAction(QIcon(":/pixmaps/filenew.xpm"), tr("&New"), this);
      newAct->setShortcut(tr("Ctrl+N"));
      newAct->setStatusTip(tr("Create a new file"));
      connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

      
      openAct2 = new QAction(QIcon(":/pixmaps/fileopen.xpm"), tr("&Open..."), this);
      openAct2->setShortcut(tr("Ctrl+O"));
      openAct2->setStatusTip(tr("Open an existing file"));
      connect(openAct2, SIGNAL(triggered()), this, SLOT(open2()));
      
      openAct = new QAction(QIcon(":/pixmaps/fileopen.xpm"), tr("&Open..."), this);
      openAct->setShortcut(tr("Ctrl+O"));
      openAct->setStatusTip(tr("Open an existing file"));
      connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

      saveAct = new QAction(QIcon(":/pixmaps/filesave.xpm"), tr("&Save"), this);
      saveAct->setShortcut(tr("Ctrl+S"));
      saveAct->setStatusTip(tr("Save the document to disk"));
      connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

      saveAsAct = new QAction(tr("Save &As..."), this);
      saveAsAct->setStatusTip(tr("Save the document under a new name"));
      connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

      exitAct = new QAction(tr("E&xit"), this);
      exitAct->setShortcut(tr("Ctrl+Q"));
      exitAct->setStatusTip(tr("Exit the application"));
      connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

      cutAct = new QAction(QIcon(":/pixmaps/editcut.xpm"), tr("Cu&t"), this);
      cutAct->setShortcut(tr("Ctrl+X"));
      cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                              "clipboard"));
      connect(cutAct, SIGNAL(triggered()), mytabs, SLOT(cut()));

      copyAct = new QAction(QIcon(":/pixmaps/editcopy.xpm"), tr("&Copy"), this);
      copyAct->setShortcut(tr("Ctrl+C"));
      copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                              "clipboard"));
      connect(copyAct, SIGNAL(triggered()), mytabs, SLOT(copy()));

      pasteAct = new QAction(QIcon(":/pixmaps/editpaste.xpm"), tr("&Paste"), this);
      pasteAct->setShortcut(tr("Ctrl+V"));
      pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
      connect(pasteAct, SIGNAL(triggered()), mytabs, SLOT(paste()));

      connect(mytabs, SIGNAL(isPastable(bool)),
                pasteAct, SLOT(setEnabled(bool)));

      connect(mytabs, SIGNAL(isCopiable(bool)),
                copyAct, SLOT(setEnabled(bool)));


      connect(mytabs, SIGNAL(isCutable(bool)),
                cutAct, SLOT(setEnabled(bool)));


      
      m_displayPreferencesDialog = new QAction(QIcon(":/pixmaps/gnome_settings.png"), tr("&Preferences"), this);
      m_displayPreferencesDialog->setShortcut(tr("Ctrl+P"));
      m_displayPreferencesDialog->setStatusTip(tr("Display preferences dialog box"));
      connect(m_displayPreferencesDialog, SIGNAL(triggered()), this, SLOT(show_preferences()));
      
      for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
      }

      showhidePlayer = new QAction(tr("Show/hide &AudioPlayer"), this);
      showhidePlayer->setStatusTip(tr("Show/hide Audio Player"));
      connect(showhidePlayer, SIGNAL(triggered()), this, SLOT(showhideaudioplayer()));

      showhideExplorer= new QAction(tr("Show/hide &file explorer"), this);
      showhideExplorer->setStatusTip(tr("Show/hide file explorer"));
      connect(showhideExplorer, SIGNAL(triggered()), this, SLOT(showhideexplorer()));

      aboutAct = new QAction(tr("&About"), this);
      aboutAct->setStatusTip(tr("Show the application's About box"));
      connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

      aboutQtAct = new QAction(tr("About &Qt"), this);
      aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
      connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

      cutAct->setEnabled(false);
      copyAct->setEnabled(false);
      pasteAct->setEnabled(false);
      parseDirAct = new QAction(tr("Parse Directory"), this);
      parseDirAct->setStatusTip(tr("Find every Mp3 files in a directory tree"));
      connect(parseDirAct, SIGNAL(triggered()), this, SLOT(openDir()));
      
      
      parentDirAct = new QAction(QIcon(":/pixmaps/arrow-up.xpm"),tr("Up"), this);
      parentDirAct->setStatusTip(tr("Use the parent directory as root directory"));
      connect(parentDirAct, SIGNAL(triggered()), this, SLOT(gotoparentDir()));
     
      useDirAct = new QAction(tr("Define as root"), this);
      useDirAct->setStatusTip(tr("Use this directory as root directory"));
      connect(useDirAct, SIGNAL(triggered()), this, SLOT(useDirasRoot()));
      
      
      addfileAct= new QAction(QIcon(":/pixmaps/filenew.xpm"),tr("Add one file..."), this);
      addfileAct->setStatusTip(tr("Add to the playlist one file"));
      connect(addfileAct, SIGNAL(triggered()), this, SLOT(openMusicFile()));
      
      
      
      adddirAct = new QAction(QIcon(":/pixmaps/fileopen.xpm"),tr("Explore a directory..."), this);
      adddirAct->setStatusTip(tr("Find every Mp3 files in a directory tree"));
      connect(adddirAct, SIGNAL(triggered()), this, SLOT(addDir()));
      
      
      
      selectBoxAct = new QAction(QIcon(":/pixmaps/fileopen.xpm"),tr("Choose a dir..."), this);
      selectBoxAct->setStatusTip(tr("Select a root directory"));
      connect(selectBoxAct, SIGNAL(triggered()), this, SLOT(selectRootDir()));
      
      startsearch= new QAction(QIcon(":/pixmaps/viewmag.png"),tr("Find"), this);
      startsearch->setShortcut(tr("Ctrl+F"));
      startsearch->setStatusTip(tr("Find a song"));
      connect(startsearch, SIGNAL(triggered()), this, SLOT(Seekfile()));
      
      nextsearch= new QAction(QIcon(":/pixmaps/next.png"),tr("Find Next"), this);
      nextsearch->setShortcut(tr("F3"));
      nextsearch->setStatusTip(tr("Find the next song"));
      connect(nextsearch, SIGNAL(triggered()), this, SLOT(nextfile()));
      
      prevsearch= new QAction(QIcon(":/pixmaps/previous.png"),tr("Find Previous"), this);
      prevsearch->setShortcut(tr("Shift+F3"));
      prevsearch->setStatusTip(tr("Find the previous song"));
      connect(prevsearch, SIGNAL(triggered()), this, SLOT(previousfile()));
      
      
      importPLS= new QAction(tr("PLS"), this);
      importXML= new QAction(tr("XML"), this);
      connect(importPLS, SIGNAL(triggered()), this, SLOT(OnImport()));
      connect(importXML, SIGNAL(triggered()), this, SLOT(OnImport()));
      
      
      exportXML= new QAction(tr("XML"), this);
      connect(exportXML, SIGNAL(triggered()), this, SLOT(onExport()));
      exportPLS= new QAction(tr("PLS"), this);
      connect(exportPLS, SIGNAL(triggered()), this, SLOT(onExport()));
      exportPDF= new QAction(tr("PDF"), this);
      connect(exportPDF, SIGNAL(triggered()), this, SLOT(onExport()));
      exportHTML= new QAction(tr("HTML"), this);
      connect(exportHTML, SIGNAL(triggered()), this, SLOT(onExport()));
      exportcsv= new QAction(tr("CSV"), this);
      connect(exportcsv, SIGNAL(triggered()), this, SLOT(onExport()));
      


     AddList  = new QAction(tr("Add PlayList..."), this);
     AddList->setStatusTip(tr("Add a PlayList at the end of this one"));
     connect(AddList, SIGNAL(triggered()), this, SLOT(OnAddList()));

     rmRedondance  = new QAction(tr("Find/Remove redondance..."), this);
     rmRedondance->setStatusTip(tr("Add a PlayList at the end of this one"));


      doAction= new QAction(tr("Redo"), this);
      
      undoaction= new QAction(tr("Undo"), this);
      undoaction->setShortcut(tr("Ctrl+z"));
      undoaction->setEnabled(false);
      connect(undoaction, SIGNAL(triggered()), mytabs, SLOT(cancel()));
      connect(mytabs, SIGNAL(actiondone(int )), this, SLOT(enabledUndo(int )));
      
      
      
      assistantAct = new QAction(tr("Help Contents"), this);
      assistantAct->setShortcut(tr("F1"));
      connect(assistantAct, SIGNAL(triggered()), this, SLOT(assistant()));
      
      FindingAct = new QAction(tr("Seeking assistant"), this);
      FindingAct->setShortcut(tr("j"));
      connect(FindingAct, SIGNAL(triggered()), this, SLOT(FindingAssis()));

      
}

void PlayListGenerator::createMenus()
{
      fileMenu = menuBar()->addMenu(tr("&File"));
      fileMenu->addAction(newAct);
      fileMenu->addAction(openAct);
      fileMenu->addAction(saveAct);
      fileMenu->addAction(saveAsAct);
      fileMenu->addSeparator();
     
      
      QMenu * import=fileMenu->addMenu (tr("Import"));
      
      import->setStatusTip(tr("Load a playlist from different file types."));

      
      import->addAction(importPLS);
      import->addAction(importXML);
      QMenu * exportmenu=fileMenu->addMenu (tr("Export"));
      
      exportmenu->setStatusTip(tr("Export the playlist in different file formats."));

      
      exportmenu->addAction(exportPLS);
      exportmenu->addAction(exportXML);
      exportmenu->addAction(exportPDF);
      exportmenu->addAction(exportHTML);
      exportmenu->addAction(exportcsv);
      
      separatorAction = fileMenu->addSeparator();
      for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
      
      fileMenu->addSeparator();
      fileMenu->addAction(exitAct);

      editMenu = menuBar()->addMenu(tr("&Edit"));
      editMenu->addAction(undoaction);
      editMenu->addSeparator();
      editMenu->addAction(cutAct);
      editMenu->addAction(copyAct);
      editMenu->addAction(pasteAct);
      editMenu->addSeparator();
      
      editMenu->addAction(startsearch);
      editMenu->addAction(nextsearch);
      editMenu->addAction(prevsearch);
      editMenu->addSeparator();
      
      editMenu->addAction(FindingAct);
     editMenu->addSeparator();
      editMenu->addAction(selectBoxAct);
      editMenu->addSeparator();
      editMenu->addAction(m_displayPreferencesDialog);


      viewMenu = menuBar()->addMenu(tr("&View"));
      mytabs->InitViewmenu(viewMenu);
      viewMenu->addAction(showhidePlayer);    
      viewMenu->addAction(showhideExplorer);
      
      addMenu= menuBar()->addMenu(tr("&List"));
      addMenu->addAction(addfileAct);
      addMenu->addAction(adddirAct);
      addMenu->addSeparator();
      addMenu->addAction(AddList);
      addMenu->addAction(rmRedondance);

        pluginMenu = menuBar()->addMenu(tr("&Plugin"));
        pluginmanager->setmenu(pluginMenu);

      helpMenu = menuBar()->addMenu(tr("&Help"));
      helpMenu->addAction(assistantAct);
      helpMenu->addSeparator();
      helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
    




}
void PlayListGenerator::assistant()
{
  
     // assistantClient->showPage("/home/renaud/applications/PlayListGenerator/documentation/"+QLocale::system().name()+"/index.html");
}
void PlayListGenerator::createToolBars()
{
      fileToolBar = addToolBar(tr("File"));
      fileToolBar->addAction(newAct);
      fileToolBar->addAction(openAct);
      fileToolBar->addAction(saveAct);
      
      editToolBar = addToolBar(tr("Edit"));
      editToolBar->addAction(cutAct);
      editToolBar->addAction(copyAct);
      editToolBar->addAction(pasteAct);
     
      
      searchToolbar = new QToolBar(tr("search"),this);
      searchEdit = new QLineEdit;
      //searchEdit->setEditable(true);
      searchEdit->setFixedWidth(SIZE_DISPLAY_EDITLINE);

      m_completer = new QCompleter(m_searchList, this);
      searchEdit->setCompleter(m_completer);
 
      QSizePolicy a(QSizePolicy::Fixed,QSizePolicy::Fixed);
      searchEdit->setSizePolicy (a);



      
      searchToolbar->addWidget(searchEdit);
      connect(searchEdit,SIGNAL(returnPressed()),this, SLOT(Seekfile()));
      searchToolbar->addAction(startsearch);
      searchToolbar->addAction(prevsearch);
      searchToolbar->addAction(nextsearch);    
      addToolBar(searchToolbar);


}
void PlayListGenerator::OnAddList()
{
        //
        QString save = curFile;
        QString fileName = QFileDialog::getOpenFileName(this,tr("Play List Generator"),".",tr(
            "Supported files (*.m3u *.qpl)\nM3U playList files (*.m3u)\nBinary playList files (*.qpl)"));
            if (!fileName.isEmpty())
            loadFile(fileName);

         //save = curFile;
         setCurrentFile(save);
}
void PlayListGenerator::createStatusBar()
{
      statusBar()->showMessage(tr("Ready"));
}

void PlayListGenerator::readSettings()
{	 
    QSettings settings("Renaud Guezennec", "PlayListGenerator");

    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();

    QSize size = settings.value("size", QSize(400, 400)).toSize();

    bool statut = settings.value("dockplayerstatut", false).toBool();
    if(statut)
        playerdock->show();
    else
        playerdock->hide();


    resize(size);
    move(pos);

    m_searchList = settings.value("recentSearch",m_searchList).toStringList();

    recentfiles = settings.value("recentFiles").toStringList();
    mytabs->readSettings(settings);
    mypreferences->readSettings(settings);
    pluginmanager->readSettings(settings);

    updateRecentFileActions();
    if((recentfiles.size()>0)&&(mypreferences->getLoadlastfile())&&(curFile.isEmpty()))
    {
        loadFile(recentfiles[0]);
    }

    myplayer->readSettings(settings);


     
}

void PlayListGenerator::writeSettings()
{
    QSettings settings("Renaud Guezennec", "PlayListGenerator");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("recentFiles", recentfiles);

    settings.setValue("recentSearch",m_searchList);


    settings.setValue("dockplayerstatut", playerdock->isVisible());

    mytabs->writeSettings(settings);
    mypreferences->writeSettings(settings);
    pluginmanager->writeSettings(settings);

    myplayer->writeSettings(settings);

}

bool PlayListGenerator::maybeSave()
{
      if (isWindowModified()) {
            int ret = QMessageBox::warning(this, tr("PlayListGenerator"),
                        tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
            if (ret == QMessageBox::Yes)
            return save();
            else if (ret == QMessageBox::Cancel)
            return false;
      }
      return true;
}

void PlayListGenerator::loadFile(const QString &fileName)
{
      QFile file(fileName);
      
      if(fileName.endsWith(".qpl"))
      {
        if (!file.open(QFile::ReadOnly)) {
          QMessageBox::warning(this, tr("PlaylistGenerator"),
                               tr("Cannot read file %1:\n%2.")
                                   .arg(fileName)
                                   .arg(file.errorString()));
          return;
        }
        
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_4);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        in >> (*mytabs);
        QApplication::restoreOverrideCursor();
        

        setCurrentFile(fileName);
        statusBar()->showMessage(tr("File loaded"), 2000);
      }
      else
      {
        if (!file.open(QFile::ReadOnly | QFile::Text)) 
        {
                QMessageBox::warning(this, tr("PlayListGenerator"),
                                tr("Cannot read file %1:\n%2.")
                                .arg(fileName)
                                .arg(file.errorString()));
                return;
        }
                
                QTextStream in(&file);
                
                QApplication::setOverrideCursor(Qt::WaitCursor);
                
                
                
                
                
                in >> (*mytabs);
                
                
                QApplication::restoreOverrideCursor();
                
                
                setCurrentFile(fileName);
                statusBar()->showMessage(tr("File loaded"), 2000);
                statusBar()->showMessage(tr("Time: %1 seconds").arg(mytabs->totalTime()));

      }
      

}

bool PlayListGenerator::saveFile(const QString &fileName)
{
      QFile file(fileName);

      if(fileName.endsWith(".qpl"))
      {

        if (!file.open(QFile::WriteOnly)) {
          QMessageBox::warning(this, tr("PlayListGenerator"),
                               tr("Cannot write file %1:\n%2.")
                                   .arg(fileName)
                                   .arg(file.errorString()));
          return false;
        }

        QDataStream out(&file);

        QApplication::setOverrideCursor(Qt::WaitCursor);
        out << (*mytabs);
        
       // file.flush();
        QApplication::restoreOverrideCursor();

      }
      else
      {
        
       
      
      
                if (!file.open(QFile::WriteOnly | QFile::Text)) {
                        QMessageBox::warning(this, tr("PlaylistGenerator"),
                                        tr("Cannot write file %1:\n%2.")
                                        .arg(fileName)
                                        .arg(file.errorString()));
                        return false;
                }

        QTextStream out(&file);
        
        QApplication::setOverrideCursor(Qt::WaitCursor);
        out << (*mytabs);
        QApplication::restoreOverrideCursor();
      }
      setCurrentFile(fileName);
      statusBar()->showMessage(tr("File saved"), 2000);

      return true;
}

void PlayListGenerator::setCurrentFile(const QString &fileName)
{
		

      curFile = fileName;
		
      setWindowModified(false);

      QString shownName;
      if (curFile.isEmpty())
          shownName = tr("untitled.qpl");
      else
      {
            
        shownName = strippedName(curFile);
        recentfiles.removeAll(curFile);
        recentfiles.prepend(curFile);
        updateRecentFileActions();
         
        
      }
      setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("PlaylistGenerator - V0.9.1")));
}

QString PlayListGenerator::strippedName(const QString &fullFileName)
{
      return QFileInfo(fullFileName).fileName();
}
void PlayListGenerator::openMusicFile()
{
    QString *fileName = new QString(QFileDialog::getOpenFileName(this,tr("Play List Generator"),".",FileSupported));
  
     if(!fileName->isEmpty())
     {
  	mytabs->addfile(*fileName);
     }

}

void PlayListGenerator::PopupMenurequested(const QPoint & pos)
{

  curDir = model->filePath(tree->indexAt(pos));
        
  
 
       
 
 
 
  QMenu menu(tree);
 
  menu.addAction(parseDirAct);
  menu.addAction(parentDirAct);
  
  menu.addAction(useDirAct);
  menu.addAction(selectBoxAct);
  menu.addSeparator();
  
  menu.addAction(openAct2);
  if (curDir.isEmpty())
  {
    parseDirAct->setEnabled(false);
    useDirAct->setEnabled(false);
    parentDirAct->setEnabled(true);
    
    openAct2->setEnabled(false);
    
  }
  else
  {
    
    QFileInfo a(curDir);
    if((a.isFile())&&((a.suffix().toLower()=="m3u")||(a.suffix().toLower()=="qpl")))
    {
      parseDirAct->setEnabled(false);
      useDirAct->setEnabled(false);
      parentDirAct->setEnabled(false);
      openAct2->setEnabled(true);
    }
    else if(a.isDir())
    {
      openAct2->setEnabled(false);
      parseDirAct->setEnabled(true);
      parentDirAct->setEnabled(true);
      useDirAct->setEnabled(true);
    }
  }
  menu.exec(QCursor::pos());
}
 



void PlayListGenerator::openDir()
{
  mytabs->openDir(curDir);
  documentWasModified();
}
void PlayListGenerator::gotoparentDir()
{
  QDir* a = new QDir(model->filePath(tree->rootIndex()));
  a->cdUp();
  tree->setRootIndex(model->index(a->path()));
}   
void PlayListGenerator::useDirasRoot()
{
  tree->setRootIndex(model->index(curDir));
}
void PlayListGenerator::selectRootDir()
{
  QString fileName = QFileDialog::getExistingDirectory(this);
  if (!fileName.isEmpty())
    tree->setRootIndex(model->index(fileName));
}
void PlayListGenerator::Seekfile()
{
  if(mysearch!=NULL)
  {
    delete mysearch;
  }
  
  
  if(!searchEdit->text().isEmpty())
  {
        mysearch=new Search;
        mysearch->current=-1;
        mysearch->regex = searchEdit->text();
        m_searchList.append(searchEdit->text());
        mysearch->myseeker =new VisitorMediaSeeker(mysearch->regex);
        mysearch->list = new QList<int>;
        
        connect(mysearch->myseeker, SIGNAL(FindItem(int)), this, SLOT(additemfound(int)));
        
        mysearch->mythread = new Thread(mytabs->getmyPlaylist()->getP_myPlaylist());
        mysearch->mythread->setVisitor(mysearch->myseeker);
        mysearch->mythread->start();
  }
  else
  {
    searchEdit->setFocus();
  }
}

void PlayListGenerator::nextfile()
{
  if((mysearch!=NULL)&&(mysearch->list->size()>0))
  {
    mysearch->current++;
    if(mysearch->list->size()<=mysearch->current)
    {
      mysearch->current=0;
    }
    mytabs->ShowandSelectRow( mysearch->list->at(mysearch->current));
  }
}   
void PlayListGenerator::previousfile()
{
  if((mysearch!=NULL)&&(mysearch->list->size()>0))
  {
    mysearch->current--;
    if(0>mysearch->current)
    {
      mysearch->current = mysearch->list->size()-1;
    }
    mytabs->ShowandSelectRow( mysearch->list->at(mysearch->current));
  }
}
void PlayListGenerator::additemfound(int index)
{
  if(mysearch!=NULL)
  {
    mysearch->list->append(index);
    if(mysearch->current==-1)
       nextfile();
  }
}
void PlayListGenerator::updateRecentFileActions()
{
    //qDebug() << "Size of recentfiles:"<< recentfiles.size() ;

  QMutableStringListIterator i(recentfiles);
  while(i.hasNext())
  {
     QString path = i.next();
    if(!QFile::exists(path))
    {
      i.remove();
    }
   
    for(int j = 0; j<mypreferences->getNb_recentfiles();++j)
    {
    	
      if(j<recentfiles.count())
      {
       QString Text = tr("&%1 %2").arg(j+1).arg(strippedName(recentfiles[j])); 
        
       recentFileActions[j]->setText(Text);
       recentFileActions[j]->setData(recentfiles[j]);
       recentFileActions[j]->setVisible(true);
       /*if((j==0)&&(mypreferences->getLoadlastfile())&&(curFile.isEmpty()))
       {
       	

            loadFile(recentfiles[j]);

        }*/
      }

    }
    separatorAction->setVisible(!recentfiles.isEmpty());

  }
}
void PlayListGenerator::openRecentFile()
{
  if (maybeSave()) {
    mytabs->reset();
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
      loadFile(action->data().toString());
  }
}
void PlayListGenerator::OnImport()
{
  QAction *action = qobject_cast<QAction *>(sender());
  ImportParser* p=NULL;
  QString fileName;
  if(action==importPLS)
  {
    fileName = QFileDialog::getOpenFileName(this,tr("Play List Generator"),".",tr("pls playList files (*.PLS)"));
    p = new PLSimport;
  }
  else if(importXML==action)
  {
    fileName = QFileDialog::getOpenFileName(this,tr("Play List Generator"),".",tr("Xml playList files (*.xml)"));
    p = new XmlImport;
  }

  if(p!=NULL)
  {

        p->setFilename(fileName);
        p->readFile();
        mytabs->setImportparser(p);
  }

}
void PlayListGenerator::show_preferences()
{
  mypreferences_dialog = new Preferences_Impl_Dialog(mytabs,this);
   mypreferences_dialog->exec();
  

}
void PlayListGenerator::onExport()
{
  mywizzard = new Wizzardexport(mytabs);
  QAction *action = qobject_cast<QAction *>(sender());
  if (action)
  {
    if(exportXML==action)
      mywizzard->setExportType(XML);
    else if(exportPLS==action)
      mywizzard->setExportType(PLS);
    else if(exportPDF==action)
      mywizzard->setExportType(PDF);
    else if(exportHTML==action)
      mywizzard->setExportType(HTML);  
    else if(exportcsv==action)
      mywizzard->setExportType(CVS);    
  }         
 
  
 if(mywizzard->exec())
 {
   QString* exportfileName = new QString;
   *exportfileName = QFileDialog::getSaveFileName(this,tr("Play List Generator"),".",mywizzard->getFilter());
   if(!exportfileName->isEmpty())
   {
        PL_Document* docview = mywizzard->getView();
        docview->setFilename(exportfileName);
        PL_ImplDocModel* p =(PL_ImplDocModel*) mywizzard->getModel();
        p->setHeaderList(mytabs->getheaderlist());
        docview->setModel(p);
        docview->setMap(mywizzard->getMap());
        docview->write();
   }
   delete exportfileName;
 }
}

void PlayListGenerator::enabledUndo(int a)
{
 if(a>0)
 {
   undoaction->setEnabled(true);
 }
 else
   undoaction->setEnabled(false);
}
void PlayListGenerator::initializeAssistant()
{
 /* assistantClient = new QAssistantClient(QLibraryInfo::location(QLibraryInfo::BinariesPath), this);

  QStringList arguments;
  arguments << "-profile" << mypreferences->getUri_documentation();
  assistantClient->setArguments(arguments);*/
}
void PlayListGenerator::addDockProgressbar()
{   
    Progressdock->show();
}
void PlayListGenerator::removeDockProgress()
{
      	
     	Progressdock->hide();
}


void PlayListGenerator::valueProgressBarChanged(int x)
{
	workinprogress->setValue(x);
}

void PlayListGenerator::addDockplayer(const QModelIndex & index)
{
 	if(!mypreferences->getShowPlayerOnStartReading())
		showDockplayer();
		
		myplayer->setFile(index);
      	
}
void PlayListGenerator::showDockplayer()
{
                playerdock->show();
}
void PlayListGenerator::removeDockPlayer()
{
      	playerdock->hide();
}
void PlayListGenerator::showhideaudioplayer()
 {
	  	if(playerdock->isHidden())
	  		playerdock->show();
	  	else
	  		playerdock->hide();
}
void PlayListGenerator::FindingAssis()
{
        mySearchFilter->show();
}
void PlayListGenerator::hideFindingAssist(/*const QModelIndex & index*/)
{
    mySearchFilter->hide();


}


void PlayListGenerator::showhideexplorer()
{
        if(m_treedock->isHidden())
            m_treedock->show();
	  	else
            m_treedock->hide();
}

PlayListGenerator::~PlayListGenerator()
{

    if(NULL!=mywizzard)
      delete mywizzard;
    if(NULL!=model)
      delete model;
    if(NULL!=tree)
      delete tree;
    if(NULL!=mytabs)
      delete mytabs;

  //delete mainSplitter;

}

