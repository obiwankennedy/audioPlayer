/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
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
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QList>
#include <QTextStream>
#include "playlistitem.h"
#include "visitormedia.h"
#include "pl_itemcompare.h"
/**
 * @author Renaud Guezennec <renaud.guezennec at gmail dot com>
 * \class Playlist
 * \brief this class bring together all methods useful on the playlist as insert,remove,sort.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no          
*/
class Playlist
{
private:   
     QList<PlaylistItem*>* myPlaylist;
     Playlist();
     ~Playlist();


public:
    static Playlist* getInstance();
    static void kill();
    void append(PlaylistItem* a);
    PlaylistItem* value(int x) const;
    int size();
    QList<PlaylistItem*> getmyPlaylist() const;
    QList<PlaylistItem*>* getP_myPlaylist() const;
    void insert(QList<PlaylistItem*>* os);
    void insert(int i,QList<PlaylistItem*>* os);
    void remove(PlaylistItem* a);
    void getdownItem(int from,int to);//When the selection goes to the bottom.
    void getupItem(int from,int to);//when the selection goes to the top.
    void move(int from,int to);
    int item2index(PlaylistItem* b);
    void insert(int a,PlaylistItem* b);

    void removeAt(int a);
    void reset();
    void sort(int start,QList<PlaylistItem*>* _myselection,DataField _criteria,Qt::SortOrder order);
    void addfile(QString& filename);    
    qlonglong reckOnTime();
    PlaylistItem*& operator[](int column) const;

    
    friend QTextStream& operator<<(QTextStream& os,const Playlist&);
    friend QTextStream& operator>>(QTextStream& is,Playlist&);

    friend QDataStream& operator<<(QDataStream& os,const Playlist&);
    friend QDataStream& operator>>(QDataStream& is,Playlist&);
    
private:   
  static Playlist* singleton;
  qlonglong m_totaltime;
};
//

#endif

