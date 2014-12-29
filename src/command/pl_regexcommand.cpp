#include "pl_regexcommand.h"
 pl_regexcommand::pl_regexcommand(QList<PlaylistItem*> _myselection,int _start, DataField _criteria,PL_TableView* _tableview)
: PL_COMMAND(),myselection(_myselection),start(_start),criteria(_criteria),tableview(_tableview)
 {

}

pl_regexcommand::~pl_regexcommand()
{

}

void pl_regexcommand::doCommand()
{
    int step = myselection.size()/100;
        emit Maximum(100);
        int i = 0;
        int k = 0;
        emit Minimum(i);
  foreach(PlaylistItem* a, myselection)
  {
      if(i>=step)
        {
                        emit valueChanged(++k);
                        i = 0;
                }
                QVariant ab = a->getKey()->getMember(TITLE);

                    i++;
                     QRegExp rx("(\\d+) (.*)-(.*)");



                      int pos = rx.indexIn(ab.toString());
                    if(pos != -1) {
                         rx.cap(1);
                         QVariant* artist = new QVariant( rx.cap(2));
                          QVariant* title = new QVariant( rx.cap(3));
                         a->getKey()->setValue(ARTIST,*artist,true);
                         a->getKey()->setValue(TITLE,*title,true);

                     }

  }
  emit done();
}

void pl_regexcommand::undo()
{
}
