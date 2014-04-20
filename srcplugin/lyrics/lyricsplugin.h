/***************************************************************************
 *   Copyright (C) 2009 by Renaud Guezennec   *
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
#ifndef LYRICSPLUGIN_H
#define LYRICSPLUGIN_H
#include "AbstractLyricsFinder.h"
#include <QObject>
#include <songplugin.h>
#include "lyricsviewerdock.h"

#include <QProcess>
class LyricsPlugin : public QObject,public SongInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.playlistgenerator.SongInterface.Lyrics" FILE "lyrics.json")
    Q_INTERFACES(SongInterface)


private:
    //LyricsPlugin();
    //static LyricsPlugin* singleton;
    QString* name;
    LyricsViewerDock* viewer;
    AbstractLyricsFinder* finderleos;
    AbstractLyricsFinder* finiderwikifly;
    AbstractLyricsFinder* finderwiki;
    QProcess* m_proc;
    SongFields* m_p;
    Qt::DockWidgetArea m_currentArea;
    QAction* m_menuAct;


public slots:
    void startEditing();
    void saveLyrics();
    void onlineResearch();
    //bool m_isVisible;
public:
    virtual void SetSong(SongFields* p);
    virtual QString getName();
    virtual QAction* getAction();
    virtual void stopped();
    virtual QDockWidget* getWidget();
    virtual bool hasUI();
    virtual bool isVisible();
    virtual Qt::DockWidgetArea orientation();
    virtual void readSetting(QSettings& settings);
    virtual void writeSetting(QSettings& settings);

public slots:
      virtual void show();
      virtual void refresh();
      void onError( QProcess::ProcessError error);
      void locationChanged(Qt::DockWidgetArea area);



};

#endif // LYRICSPLUGIN_H
