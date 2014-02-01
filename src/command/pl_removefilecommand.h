#ifndef PL_REMOVEFILECOMMAND_H
#define PL_REMOVEFILECOMMAND_H



#include <pl_command.h>
#include "pl_tableview.h"
#include "playlist.h"


class PL_TableView;
class PL_RemoveFileCommand : public PL_COMMAND
{



  QList<PlaylistItem*>  myselection;
  int start;

  PL_TableView* tableview;
  Playlist* myPlaylist;
public:
    PL_RemoveFileCommand(QList<PlaylistItem*> myselection,int start,PL_TableView* tableview);
    ~PL_RemoveFileCommand();
    virtual void doCommand();
    virtual void undo();
    virtual bool check();
};

#endif // PL_REMOVEFILECOMMAND_H
