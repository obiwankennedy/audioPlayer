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


#ifndef PLAYLISTGENERATOR_H
#define PLAYLISTGENERATOR_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSplitter>
#include <QTreeView>
#include <QDirModel>
#include <QTabWidget>
//#include <QAssistantClient>
#include <QProgressBar>



#include "playlistviewer.h"
#include "visitormediaseeker.h"
#include "thread.h"
#include "wizzardexport.h"
#include "preferences_Impl.h"
#include "preference_data.h"
#include "player.h"
#include "search_dialogimpl.h"
#include "songpluginmanager.h"
#include "pl_databasemanager.h"

#define SIZE_TEXT_EDITLINE 1024
#define SIZE_DISPLAY_EDITLINE 200

class QAction;
class QMenu;
class PL_DataBaseManager;

struct Search
{
  QString regex;
  QList<int>* list;
  VisitorMediaSeeker* myseeker;
  int current;
  Thread* mythread;
};
/**
        @author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PlayListGenerator
 * \brief It is the main window of PlayListGenerator
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no           
 */
class PlayListGenerator:public QMainWindow
{
      Q_OBJECT

public:
      PlayListGenerator();
      ~PlayListGenerator();
      void loadFile(const QString &fileName);
      void refreshPlugin();
      void closeApplication();

protected:
      void closeEvent(QCloseEvent *event);
      


public slots:
        void valueProgressBarChanged(int x);
        void addDockProgressbar();
      	void removeDockProgress();
        bool save();
        bool saveAs();
      	void addDockplayer(const QModelIndex & index);
      	void removeDockPlayer();
      	

private slots:
      void newFile();
      void open();
      void about();
      void documentWasModified();
      void PopupMenurequested(const QPoint & pos);
      void openDir();
      void gotoparentDir();
      void useDirasRoot();
      void selectRootDir();
      void Seekfile();
      void nextfile();
      void previousfile();
      void additemfound(int index);
      void openRecentFile();
      void onExport();
      void enabledUndo(int a);
      void open2();
      void openMusicFile();
      void addDir();
      void OnImport();
      void assistant();
      void show_preferences();
      void OnAddList();

	  void showDockplayer();
	  void showhideaudioplayer();
      void FindingAssis();
      void hideFindingAssist();

	  void showhideexplorer();
private:
      void createActions();
      void createMenus();
      void createToolBars();
      void createStatusBar();
      void readSettings();
      void writeSettings();
      bool maybeSave();

      bool saveFile(const QString &fileName);
      void setCurrentFile(const QString &fileName);
      QString strippedName(const QString &fullFileName);
      void updateRecentFileActions();
      void initializeAssistant();
      
     // QAssistantClient *assistantClient;
      
    SongPluginManager* pluginmanager;
     QDirModel* model;
     QTreeView* tree;
     
     PlayListViewer* mytabs;
//     QSplitter *mainSplitter;
     QDockWidget* m_treedock;
     QString curFile;
     QString curDir;
     QStringList recentfiles;
     QDockWidget *Progressdock;

     Search_DialogImpl* mySearchFilter;
     Player* myplayer;
     QDockWidget *playerdock;

     QProgressBar *workinprogress;
     enum { MaxRecentFiles = 5 };
     QAction *recentFileActions[MaxRecentFiles];
     QAction *separatorAction;

     
     
     
     Wizzardexport* mywizzard;
     Preferences_Impl_Dialog* mypreferences_dialog; 
     Preference_data* mypreferences;
     QMenu *fileMenu;
     QMenu *editMenu;
     QMenu *addMenu;
     QMenu *viewMenu;
     QMenu *helpMenu;
     QMenu *pluginMenu;

     QToolBar *fileToolBar;
     QToolBar *editToolBar;
     QToolBar *searchToolbar;
     
     QLineEdit *searchEdit;
     //QComboBox *searchEdit;
     QStringList m_searchList;
     QCompleter *m_completer;
     PL_DataBaseManager* m_database;

     QAction *newAct;
     QAction *openAct;
     QAction *openAct2;
     QAction *saveAct;
     QAction *saveAsAct;
     QAction *exitAct;
     
     QAction *cutAct;
     QAction *copyAct;
     QAction *pasteAct;
     
     QAction *addfileAct;
     QAction *adddirAct;
     
     QAction *aboutAct;
     QAction *aboutQtAct;
     
     QAction *showhidePlayer;
     QAction *showhideExplorer;
     
     QAction *parseDirAct;
     QAction *parentDirAct;
     
     QAction *useDirAct;
     QAction *selectBoxAct;
     
     QAction *startsearch;
     QAction *nextsearch;
     QAction *prevsearch;
     QAction *m_displayPreferencesDialog;
     QAction *assistantAct;
     
     //Import export action
     QAction *importPLS;
     QAction *importXML;
     QAction *exportXML;
     QAction *exportPLS;
     QAction *exportPDF;
     QAction *exportHTML;
     QAction *exportcsv;

     QAction *concatList;
     QAction *AddList;
     QAction *rmRedondance;


     //do undo action
     QAction *doAction;
     QAction *undoaction;
     QAction *FindingAct;
     Search* mysearch;
};

#endif
