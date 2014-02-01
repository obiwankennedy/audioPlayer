#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include <QItemDelegate>
#include "data.h"
#include "playlist.h"
/**
        @author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class TrackDelegate
 * \brief Class to re-define the display setting of rows in the tableView.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo no              
 */
class TrackDelegate : public QItemDelegate
{
    Q_OBJECT

public:
  TrackDelegate(int durationColumn,int YearColumn=-1,int BitrateColumn=-1,int GenreColumn=-1, QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    

    void setdurationColumn(int durationColumn);
    void setYearColumn(int YearColumn);
    void setBitrateColumn(int BitrateColumn);
    void setGenreColumn(int GenreColumn);
    
public slots:
	void setPlayed(int);
private:
    int durationColumn;
    int YearColumn;
    int BitrateColumn;
    int GenreColumn;
    int played;

    Playlist* myPlaylist;
   // int former_played;
};

#endif
