#include "pl_moveselection.h"

PL_MoveSelection::PL_MoveSelection(QList<PlaylistItem*> _myselection,int _start,PL_TableView* _tableview,int _dest)
 : PL_COMMAND(),myselection(_myselection),start(_start),tableview(_tableview),dest(_dest)
{
    myPlaylist = Playlist::getInstance();
}
PL_MoveSelection::~PL_MoveSelection()
{

}

void PL_MoveSelection::doCommand()
{

        int step = myselection.size()/100;
        emit Maximum(100);
        int i = 0;
        int k = 0;
        emit Minimum(i);
    for(int j = 0 ; j< myselection.size() ; j++)
    {
        if(start <= dest)
         myPlaylist->move(start,dest);
        else
          myPlaylist->move(start+j,dest+j);
        if(i>=step)
        {

                emit valueChanged(++k);
                i = 0;
         }

        i++;

    }

    emit done();


}
void PL_MoveSelection::undo()
{

for(int j = 0 ; j< myselection.size() ; j++)
    {
         myPlaylist->move(dest,start);

    }

}

