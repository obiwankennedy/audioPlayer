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
#ifndef PL_DOCUMENT_H
#define PL_DOCUMENT_H
#include <QFile>
#include "data.h"
#include "pl_documentmodel.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_Document
 * \brief Abstract class of export the playlist. 
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no              
*/
class PL_Document
{
protected:
  Pl_DocumentModel* model;
  QString* filename;
  QList<int>* map;
public:
    PL_Document();

    virtual void write()=0;
    
   virtual  ~PL_Document();
   virtual void setFilename(QString * p);
   virtual void setModel(Pl_DocumentModel* model);
   virtual void setMap(QList<int>*_map);
};

#endif
