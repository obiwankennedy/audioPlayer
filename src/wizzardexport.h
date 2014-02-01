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
#ifndef WIZZARDEXPORT_H
#define WIZZARDEXPORT_H

#include <QDialog>
#include "ui_wizzardexport.h"
#include "data.h"
#include "document/pl_document.h"
#include "document/pl_documentmodel.h"
#include "pl_tableview.h"
#include "playlistviewer.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class Wizzardexport  
 * \brief Dialog box Class to show the exportation wizzard. Inherit from QDialog and Ui::WizzardExport (Qt Designer file)
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo no       
*/

//class Pl_DocumentModel;
class Wizzardexport : public QDialog, private Ui::WizzardExport
{
  Q_OBJECT
      QStringList fieldlist;

      PlayListViewer* view;
public:
  Wizzardexport(PlayListViewer * p);

    virtual ~Wizzardexport();
    void setExportType(TypeOfExport x);
    void initAction();
    QString getFilter();
    /*!\fn PL_Document* getView();
     * \return : a configurated View object.
     */ 
    PL_Document* getView();
    Pl_DocumentModel* getModel();
    QList<int>*  getMap();
    
 public slots:
   void onAdd();
   void onRemove();
   void idtoidActived();
   void onChangedList();
};

#endif
