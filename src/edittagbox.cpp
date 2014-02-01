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
#include "edittagbox.h"
#include <QTextStream>
#include <QFileDialog>
EditTagBox::EditTagBox(QWidget *parent,QList<QModelIndex> *mylist,int i)
  : QDialog(parent)
{
  setupUi(this);
  myselection=mylist;

  urichanged = false;

  if(myselection->size()>i)
  {
  	
    TitleEdit->setReadOnly(true);
    
    //setReadOnly ( bool )
        cbtitre->setEnabled(false);
    uriTextedit->setReadOnly(true);
  }
  
  ItemDecorator* item=NULL;
  myPlaylist = Playlist::getInstance();

  QModelIndex pIndex= myselection->takeFirst();
  PlaylistItem* pItem = myPlaylist->value(pIndex.row());
                
  item = pItem->getKey();
      
  oldtitle=new QString;
  *oldtitle=item->getMember(TITLE).toString();
  
  oldartist=new QString;
  *oldartist=item->getMember(ARTIST).toString();
  
  oldcomment= new QString;
  
  oldalbum= new QString;
  *oldalbum=item->getMember(ALBUM).toString();


   
    TitleEdit->setText(item->getMember(TITLE).toString());
    
    artistEdit->setText(item->getMember(ARTIST).toString());
      
    albumEdit->setText(item->getMember(ALBUM).toString());
    commetEdit->setText(item->getMember(COMMENT).toString());
    lineEdit->setText(item->getMember(YEAR).toString());

    trackEdit->setText(item->getMember(TRACK).toString());
     
    bool ok;
    genreCombobox->addItems(listgenre);
    oldgenre = item->getMember(GENRE).toInt(&ok);
    genreCombobox->setCurrentIndex(item->getMember(GENRE).toInt(&ok));


    oldtrack=item->getMember(TRACK).toInt(&ok);


    QValidator *validator = new QIntValidator(1, 999, this);
    trackEdit->setValidator(validator);
     
    olduri = new QString;
    
    *olduri = pItem->getURI();
 
    uriTextedit->setText(*olduri);
    
    QTime* time=new QTime();

    int timeInt;
    timeInt = item->getMember(TIME).toInt(&ok);
    if(ok)
    {
             (*time)= time->addMSecs(timeInt);
             timeEdit->setDisplayFormat (QString::fromUtf8("mm.ss"));
              timeEdit->setTime(*time);
    }
    oldyear = item->getMember(YEAR).toInt(&ok);
     
    cbgenre->setChecked(false);
    cbcomment->setChecked(false);
    cbalbum->setChecked(false);
    cbartist->setChecked(false);
    cbtitre->setChecked(false);
    cbTrack->setChecked(false);
    
  connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
  

  
  connect(cancelbutton,SIGNAL(clicked()),this,SLOT(reject()));
  
 
  connect(this->artistEdit,SIGNAL(textEdited(const QString & )),this,SLOT(changedartist(const QString & )));
  connect(this->genreCombobox,SIGNAL(currentIndexChanged ( int )),this,SLOT(changedgenre(int)));
  connect(this->albumEdit,SIGNAL(textEdited(const QString & )),this,SLOT(changedalbum(const QString & )));
  connect(this->commetEdit,SIGNAL(textEdited(const QString & )),this,SLOT(changedcomment(const QString & )));
  connect(this->TitleEdit,SIGNAL(textEdited(const QString & )),this,SLOT(changedtitle(const QString & )));
  connect(this->lineEdit,SIGNAL(textEdited(const QString & )),this,SLOT(changedYear(const QString &)));
  connect(this->trackEdit,SIGNAL(textEdited(const QString & )),this,SLOT(changedTrack(const QString &)));
  connect(this->fileBrowser,SIGNAL(clicked()),this,SLOT(changeUri()));

}


EditTagBox::~EditTagBox()
{
  
}
void EditTagBox::changeUri()
{
  QString* fileName = new QString;
   QFileInfo qfi(uriTextedit->text());
  
	QDir mydir =  qfi.absoluteDir ();
	while((!mydir.exists()))
	{
		
                if(!mydir.cdUp())
                    if(!mydir.cd("../.."))
                        mydir=QDir::home();



	}
  *fileName= QFileDialog::getOpenFileName(this,tr("Play List Generator"),mydir.absolutePath() ,tr(
      "Supported files (*.mp3)\nAll kind of file files (*.*)"));
  if (!fileName->isEmpty())
  {
    urichanged = true;
    uriTextedit->setText(*fileName);
  }
}
void EditTagBox::changedgenre(int x)
{
  if(x!=oldgenre)
    cbgenre->setChecked(true);
  else
    cbgenre->setChecked(false);
}
void EditTagBox::changedtitle(const QString & text)
{
  if(text!=oldtitle)
  cbtitre->setChecked(true);
  else
    cbtitre->setChecked(false);
}
void EditTagBox::changedartist(const QString & text)
{
  if(text!=oldartist)
  cbartist->setChecked(true);
  else
    cbartist->setChecked(false);
}
void EditTagBox::changedalbum(const QString & text)
{
  if(text!=oldalbum)
     cbalbum->setChecked(true);
  else
    cbalbum->setChecked(false);
  
}
void EditTagBox::changedTrack(const QString & text)
{
    bool ok;
   int newy=  text.toInt(&ok);
    if((ok)&&(newy!=oldtrack))
       cbalbum->setChecked(true);
    else
      cbalbum->setChecked(false);
}

void EditTagBox::changedcomment(const QString & text)
{
  if(text!=oldcomment)
  cbcomment->setChecked(true);
  else
    cbcomment->setChecked(false);  
}
void EditTagBox::changedYear(const QString & text)
{
  bool ok;
 int newy=  text.toInt(&ok);
 if((ok)&&(newy!=oldyear))
    cbYear->setChecked(true);
  else
    cbYear->setChecked(false); 
}
bool EditTagBox::uriChanged()
{
  return urichanged;
 
}
