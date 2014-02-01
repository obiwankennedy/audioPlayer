#ifndef PL_MOVESELECTION_H
#define PL_MOVESELECTION_H

#include <pl_command.h>
#include "pl_tableview.h"
#include "playlist.h"

class PL_MoveSelection : public PL_COMMAND
{
    QList<PlaylistItem*>  myselection;
    Playlist* myPlaylist;

   int start;
   PL_TableView* tableview;
   int dest;
public:
    PL_MoveSelection(QList<PlaylistItem*> _myselection,int _start,PL_TableView* _tableview,int dest);
    ~PL_MoveSelection();
    virtual void doCommand();
    virtual void undo();

};

#endif // PL_MOVESELECTION_H
