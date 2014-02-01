#ifndef SEARCH_DIALOGIMPL_H
#define SEARCH_DIALOGIMPL_H
//
#include <QDialog>
#include "playlist.h"
#include "ui_findingassistant.h"
#include "searchdialogitem.h"
#include "searchmodel.h"
//
enum {EMPTY,INCREASING,DECREASING};

class Search_DialogImpl : public QDialog, public Ui::Dialog
{
Q_OBJECT
	 QString* pattern;
	 int length_pattern;
	 Playlist* myPlaylist;
	 QList<PlaylistItem*>* selection;
         SearchModel* modelsearch;
         int bahaviorList;
         QStringList mylist;
       //  int indexselected;
public:
    Search_DialogImpl( QWidget * parent = 0, Qt::WindowFlags f = 0 );
        void fillSelection();
        //int getSelection();

private slots:
        void Search(QString a);
      //  void setSelected(const QModelIndex & index);

signals:
        void doubleClicked(const QModelIndex & index);

};
#endif





