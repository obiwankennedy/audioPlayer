#include "search_dialogimpl.h"
//
Search_DialogImpl::Search_DialogImpl(QWidget* parent, Qt::WindowFlags f) : QDialog(parent, f)
{
    setupUi(this);
    myPlaylist= Playlist::getInstance();
    pattern= new QString;
    length_pattern= 0;
    connect(searchfield, SIGNAL(textChanged(QString)), this, SLOT(Search(QString)));
    // connect(ListFilter,SIGNAL(doubleClicked ( const QModelIndex &  )),this, SLOT( setSelected( const QModelIndex &
    // )));
    connect(ListFilter, SIGNAL(doubleClicked(const QModelIndex&)), this, SIGNAL(doubleClicked(const QModelIndex&)));
    // fillSelection();
    modelsearch= new SearchModel(mylist);
    ListFilter->setModel(modelsearch);
    bahaviorList= EMPTY;
    // fillSelection();
    // indexselected = -1;
}
//
void Search_DialogImpl::Search(QString a)
{
    //       QTextStream out(stderr,QIODevice::WriteOnly);
    // *pattern = searchfield->text();
    // modelsearch->setPattern(pattern);
    //       out << *pattern << " " << a << endl;
    if(a.length() == 0) // départ
    {
        bahaviorList= EMPTY;
        length_pattern= a.length();
        // selection = myPlaylist->getP_myPlaylist();
    }
    else
    {
        if(length_pattern > a.length()) // augmentation du pattern
        {
            length_pattern= a.length();
            bahaviorList= INCREASING;
            // selection = myPlaylist->getP_myPlaylist();
        }
        else if(length_pattern < a.length()) // Réduction du pattern.
        {
            length_pattern= a.length();
            bahaviorList= DECREASING;
            // selection = myPlaylist->getP_myPlaylist();
        }
    }
    int i= 0;
    // out << *pattern << " " << bahaviorList << length_pattern << endl;
    foreach(QString p, mylist)
    {
        if((bahaviorList == DECREASING) || ((!ListFilter->isRowHidden(i)) && (bahaviorList == INCREASING)))
        {
            if(!p.contains(a, Qt::CaseInsensitive))
                ListFilter->setRowHidden(i, true);
            else
                ListFilter->setRowHidden(i, false);
        }
        else if(bahaviorList == EMPTY)
        {
            ListFilter->setRowHidden(i, false);
        }
        i++;
    }
}
void Search_DialogImpl::fillSelection()
{
    foreach(PlaylistItem* p, myPlaylist->getmyPlaylist())
    {
        mylist.append(p->toString());
    }
}
/*int Search_DialogImpl::getSelection()
{
    return indexselected;

}*/
/*void Search_DialogImpl::setSelected( const QModelIndex & index)
{
    QTextStream out(stderr,QIODevice::WriteOnly);

      indexselected=  index.row();
    out <<    indexselected << endl;


}*/
