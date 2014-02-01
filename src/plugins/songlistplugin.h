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
#ifndef SONGLISTPLUGIN_H
#define SONGLISTPLUGIN_H

#include <playlistitem.h>
#include <QDockWidget>
#include "data.h"

class QString;
class QAction;
class PlaylistItem;
//PlayListGenerator gives all informations about the reading song and the plugin do
//what is supposed to do with it: find and display lyrics or the show the album picture.
class SongListInterface
{



    public:
        virtual ~SongListInterface() {}
        virtual void SetSong(SongFields* p,QString& uri)=0;
        virtual void stopped()=0;
        virtual QString getName()=0;
        virtual QAction* getAction()=0;
        virtual QDockWidget* getWidget()=0;
        virtual bool isVisible()=0;
        virtual Qt::DockWidgetArea orientation()=0;
        virtual bool hasUI()=0;

        virtual void readSetting()=0;
        virtual void writeSetting()=0;
   public slots:
          virtual void show()=0;
          virtual void refresh()=0;




};
Q_DECLARE_INTERFACE(SongListInterface,"org.PlayListGenerator.SongListInterface/1.0")
#endif // SONGLISTPLUGIN_H
