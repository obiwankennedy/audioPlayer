#ifndef PL_FILENAMEASTITLE_H
#define PL_FILENAMEASTITLE_H

#include <pl_command.h>
#include "playlistitem.h"
#include "data.h"
#include "playlist.h"

class PL_FilenameAsTitle : public PL_COMMAND
{


    QList<PlaylistItem*>  myselection;
    Playlist* myPlaylist;

public:
    PL_FilenameAsTitle(QList<PlaylistItem*> _myselection);
    ~PL_FilenameAsTitle();
    virtual void doCommand();
    virtual void undo();
};

#endif // PL_FILENAMEASTITLE_H
