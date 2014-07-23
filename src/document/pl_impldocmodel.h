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
#ifndef PL_IMPLDOCMODEL_H
#define PL_IMPLDOCMODEL_H
#include "../document/pl_documentmodel.h"

#include <QList>
#include "playlistitem.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_ImplDocModel
 * \brief Implementation of Abstract class: Pl_DocumentModel. Use for the exportation.
 * \version 1.0
 * \date 22/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no        
*/

class PL_ImplDocModel : public Pl_DocumentModel
{
  const QList<headerlistview*>* listheader;
  const QList<PlaylistItem*>* dataList;

public:
    PL_ImplDocModel();

    ~PL_ImplDocModel();
    
    int getColumnCount();
    int rowCount();
    QVariant getHeaderData(int i);
    QVariant getData(int x,int y);
    void setList(const QList<PlaylistItem*>* a);
    void setHeaderList(const QList<headerlistview*>* a);
    virtual const QString getUri(int x);
};

#endif
