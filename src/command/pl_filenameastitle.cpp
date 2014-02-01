#include "pl_filenameastitle.h"
#include <QFileInfo>

PL_FilenameAsTitle::PL_FilenameAsTitle(QList<PlaylistItem*> _myselection)
: PL_COMMAND(),myselection(_myselection)
{

}
PL_FilenameAsTitle::~PL_FilenameAsTitle()
{

}
void PL_FilenameAsTitle::doCommand()
{
 int step = myselection.size()/100;
        emit Maximum(100);
        int i = 0;
        int k = 0;
        emit Minimum(i);
    for(int j = 0 ; j< myselection.size() ; j++)
    {
        PlaylistItem* tmp = myselection[j];

        QString title(tmp->getURI());
        QString artist(tmp->getKey()->getMember(ARTIST).toString());
        QVariant basename(QFileInfo(title).baseName().replace(artist,"").replace("-","").trimmed());


        tmp->getKey()->setValue(TITLE,basename,true);

        if(i>=step)
        {

                emit valueChanged(++k);
                i = 0;
         }

        i++;

    }
    emit done();
}
void PL_FilenameAsTitle::undo()
{

}
