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
#ifndef AMENDTAG_H
#define AMENDTAG_H

#include <visitormedia.h>
#include <QList>
#include <QModelIndex>
#include <QString>
#include "playlistitem.h"
#include "playlist.h"
#include "data.h"
/**
  @author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class AmendTag
 * \brief Visitor to amend one or many PlayListItem.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no         
*/
class AmendTag : public VisitorMedia
{
//  Q_OBJECT

  Playlist* myPlaylist;
  QString* newtitle;
  QString* newalbum;
  QString* newartist;
  QString* newyear;
  int newgenre;
  QString* newcomment;
  QString* newuri;
  bool replace;
public:
    
  AmendTag(QString artist,bool bartist,QString title,bool btitre,QString album,bool balbum,int genre,bool bgenre,QString uri,bool buri,QString comment,bool bcom,QString year,bool byear,bool replace);
  virtual ~AmendTag();
    void visitMedia(ItemDecorator* media);
    void setSelection(QList<QModelIndex> *_myselection);
  
    
    //QList<QModelIndex>* getSelection();
};

#endif
