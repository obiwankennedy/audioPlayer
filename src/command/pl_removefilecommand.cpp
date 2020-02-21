#include "pl_removefilecommand.h"
#include <QMessageBox>
#include <QTextStream>
PL_RemoveFileCommand::PL_RemoveFileCommand(QList<PlaylistItem*> _myselection, int _start, PL_TableView* _tableview)
    : PL_COMMAND(), myselection(_myselection), start(_start), tableview(_tableview)
{
    myPlaylist= Playlist::getInstance();
}

PL_RemoveFileCommand::~PL_RemoveFileCommand() {}

void PL_RemoveFileCommand::doCommand()
{
    int step= myselection.size() / 100;
    emit Maximum(100);
    int i= 0;
    int k= 0;
    emit Minimum(i);
    foreach(PlaylistItem* a, myselection)
    {
        if(i >= step)
        {
            emit valueChanged(++k);
            i= 0;
        }

        if(QFile::remove(a->getURI()))
            myPlaylist->remove(a);
        i++;
    }

    emit done();
}
void PL_RemoveFileCommand::undo() {}
bool PL_RemoveFileCommand::check()
{
    int r= QMessageBox::warning(tableview, QObject::tr("Play list generator"),
        QObject::tr("Removing: Do you really want to remove from the hard disk the selected items ?"), QMessageBox::Yes,
        QMessageBox::Cancel | QMessageBox::Escape | QMessageBox::Default);
    if(r == QMessageBox::Yes)
        return true;
    else
        return false;
}
