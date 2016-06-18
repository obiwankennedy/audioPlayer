#include <QtGui>

#include "trackdelegate.h"

TrackDelegate::TrackDelegate(int durationColumn,int YearColumn,int BitrateColumn,int GenreColumn, QObject *parent)
    : QItemDelegate(parent)
{
    this->durationColumn = durationColumn;
    this->YearColumn = YearColumn;
    this->BitrateColumn = BitrateColumn;
    this->GenreColumn=GenreColumn;
    played = -1;
    myPlaylist = Playlist::getInstance();
    // former_played = -1;
}
void TrackDelegate::setPlayed(int p)
{
    /*if(played!=-1)
        former_played=played;*/

    played = p;

    /*if(former_played!=-1)
        parent*/
}
void TrackDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

    index.model()->data(index, Qt::DisplayRole).toInt();
    if((*myPlaylist)[index.row()]->isReading())
    {
        myOption.font.setBold(true);
    }

    if (index.column() == durationColumn)
    {
        int secs = index.model()->data(index, Qt::DisplayRole).toInt();
        qDebug() << "delegate" << secs;
        //secs /=1000;
        QString text = QString("%1:%2")
                .arg(secs / 60, 2, 10, QChar('0'))
                .arg(secs % 60, 2, 10, QChar('0'));

        drawDisplay(painter, myOption, myOption.rect, text);
        drawFocus(painter, myOption, myOption.rect);
    }
    else if (index.column() == YearColumn)
    {

        int years= index.model()->data(index, Qt::DisplayRole).toInt();
        QString text;
        if(years<0)
            text = tr("Unknown");
        if(years>=0)
        {
            text = QString::number(years,10);
        }

        drawDisplay(painter, myOption, myOption.rect, text);
        drawFocus(painter, myOption, myOption.rect);
    }
    else if (index.column() == BitrateColumn)
    {
        int secs = index.model()->data(index, Qt::DisplayRole).toInt();

        QString text = QString("%1 Kb/s")
                .arg(secs / 1000, 3, 10, QChar('0'));



        drawDisplay(painter, myOption, myOption.rect, text);
        drawFocus(painter, myOption, myOption.rect);
    }
    else if (index.column() == GenreColumn)
    {

        int indexi = index.model()->data(index, Qt::DisplayRole).toInt();
        QString text;
        if((indexi<listgenre.size())&&(indexi>-1))
            text = listgenre.at(indexi);
        else
            text = tr("None");




        drawDisplay(painter, myOption, myOption.rect, text);
        drawFocus(painter, myOption, myOption.rect);
    }
    else
    {

        QItemDelegate::paint(painter, myOption, index);
    }
}
void TrackDelegate::setdurationColumn(int durationColumn)
{
    this->durationColumn = durationColumn;

}
void TrackDelegate::setYearColumn(int YearColumn)
{
    this->YearColumn = YearColumn;

}
void TrackDelegate::setBitrateColumn(int BitrateColumn)
{
    this->BitrateColumn = BitrateColumn;

}
void TrackDelegate::setGenreColumn(int GenreColumn)
{
    this->GenreColumn=GenreColumn;
}




