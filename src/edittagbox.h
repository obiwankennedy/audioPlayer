/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec                                *
 *   renaud.guezennec@gmail.com                                            *
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
#ifndef EDITTAGBOX_H
#define EDITTAGBOX_H

#include <QDialog>
#include "ui_tageditordialog.h"
#include "playlist.h"
#include "itemdecorator.h"
#include "mp3decorator.h"
#include "defaultdecorator.h"
#include "data.h"
#include "amendtag.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class EditTagBox
 * \brief Dialog box to modify tag.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no          
*/
class EditTagBox : public QDialog,public Ui::TagEdition
{
  Q_OBJECT
      QList<QModelIndex> *myselection;
  Playlist* myPlaylist;
  QString* oldtitle,*oldartist,*oldcomment,*oldalbum,*olduri;
  int oldgenre,oldyear,oldtrack;
  bool urichanged;

public:
  EditTagBox(QWidget *parent = 0,QList<QModelIndex> *mylist = NULL,int i = 3);
    virtual ~EditTagBox();

    bool uriChanged();
 

public slots:
    void changedgenre(int x);
    void changedtitle(const QString & text);
    void changedartist(const QString & text);
    void changedalbum(const QString & text);
    void changedcomment(const QString & text);
    void changedYear(const QString & text);
    void changeUri();
    void changedTrack(const QString & text);


};
/*
  Ui::TagEdition ui;
  QDialog *dialog = new QDialog;
  ui.setupUi(dialog);
  dialog->show();

*/
#endif
