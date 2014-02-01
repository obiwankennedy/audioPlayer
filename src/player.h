/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
 *   renaud.guezennec@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QAction>
#include <QtGui>
#include <QMediaPlayer>
#include <QLCDNumber>

#include <QtWidgets>

//#include <phonon>
/*#include <Phonon/phononnamespace.h>
#include <Phonon/audiooutput.h>
#include <Phonon/seekslider.h>
#include <Phonon/mediaobject.h>
#include <Phonon/volumeslider.h>
#include <Phonon/backendcapabilities.h>*/

#include "playlist.h"
#include "preference_data.h"
//
#ifdef HAVE_PHONON
class Player : public QWidget//, public Ui::Form
{
Q_OBJECT
   Playlist* myPlaylist;
   int id;
   QString filename;
   PlaylistItem* m_current;
   PlaylistItem* last;
public:
	void setTitle( QString value);
	QString getTitle();
    Player( QWidget * parent = 0, Qt::WindowFlags f = 0 );
    void readSettings(QSettings& settings);
    void writeSettings(QSettings& settings);
    void stopAndClear();
	
signals: 
	void SetId(int i);
    void playingSongChanged(SongFields* a);
    void playingStop();
    void positionTime(int);


public slots:
	void setFile(const QModelIndex & index);

    /// public API for DBUS
    void nextSong();
    void playSong();
    void previousSong();
    void pauseSong();
    void stopSong();
    void setSelectionMode(int mode);
    void increaseSong(int i=1);
    void decreaseSong(int i=1);
    void seek(QString);
    void setVolume(int);

private slots:  
     void statusChanged(QMediaPlayer::MediaStatus status);
     void playerStatusChanged(QMediaPlayer::State state);
     void tick(qint64 time);
     void sourceChanged(const QMediaContent & media);
     void next();
     void previous();
     //void aboutToFinish();
     //void startPlaying(const Phonon::MediaSource &source);
     void Finish();
     void setRandom(bool);
     void setDuration(qint64);
     void setTime(int);
     #ifdef REPEAT
     void setRepeat();
#endif

private:
     int playListItem2Index(PlaylistItem* m_current);
    void setupUi();
    QMediaContent* playSong(PlaylistItem* p);


    QSlider* m_volumeSlider;
    QMediaPlayer* m_mediaPlayer;
    QSlider* m_seekSlider;



    Preference_data* mypreference;
    int position;
    ReadingMode selectedReadMode;
    QLineEdit *title;
     QAction *playAction;
     QAction *pauseAction;
     QAction *stopAction;
     QAction *nextAction;
     QAction *previousAction;
     //Phonon::Path* path;
     QPushButton *randomly;
     #ifdef REPEAT
     QCheckBox* m_repeatCheck;
    #endif

     QLCDNumber *m_timeLcd;
    void setupActions();
    QList<int> m_positions;
     int m_listposition;
#ifdef REPEAT
     bool m_repeatState;
#endif
};

#endif
#endif



