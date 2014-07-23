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
#include "wizzardexport.h"
#include <QListWidgetItem>
#include <QTextStream>
#include "document/pl_htmldoc.h"
#include "document/pl_impldocmodel.h"
#include "document/pl_cvsdoc.h"
#include "document/pl_plsdoc.h"
#include "document/pl_pdfdoc.h"
#include "document/pl_xmldoc.h"

Wizzardexport::Wizzardexport(PlayListViewer * p)
  : QDialog(p),view(p)
{
  setupUi(this);

  cbtypeofoutput->addItems(listTypeOfExport);
  //table= p->getTableview();

  
  QStringList a = SLlistcolumn;
  listofallfield->addItems(a);
  initAction();
}


Wizzardexport::~Wizzardexport()
{
  
}

void Wizzardexport::initAction()
{
  connect(addButton,SIGNAL(clicked()),this,SLOT(onAdd()));
  connect(removeButton,SIGNAL(clicked()),this,SLOT(onRemove()));

  connect(idtoidfield,SIGNAL(textEdited(const QString & )),this,SLOT(idtoidActived( )));
  
  connect(listofallfield, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(onChangedList()));
  connect(listofselectedfield, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(onChangedList()));
}
void Wizzardexport::setExportType(TypeOfExport x)
{
  cbtypeofoutput->setCurrentIndex(x);
}
void Wizzardexport::onAdd()
{

  
  if((listofallfield->currentItem()!=NULL)&&(listofallfield->isEnabled()))
  {
  listofselectedfield->addItem(listofallfield->currentItem()->text());
  delete listofallfield->currentItem();
  }
}
void Wizzardexport::onRemove()
{
  if((listofselectedfield->currentItem()!=NULL)&&(listofselectedfield->isEnabled()))
  {
  listofallfield->addItem(listofselectedfield->currentItem()->text ());
  
  delete listofselectedfield->currentItem();
  }
}

void Wizzardexport::onChangedList()
{
  QListWidget *a = qobject_cast<QListWidget *>(sender());
  if(a==listofallfield)
    listofselectedfield->setCurrentRow(-1);
  else if(a==listofselectedfield)
    listofallfield->setCurrentRow(-1);
}
QString Wizzardexport::getFilter()
{
  return  tr("%1 File: (*.%1)").arg(listTypeOfExport.at(cbtypeofoutput->currentIndex())); 
}
void Wizzardexport::idtoidActived()
{
  if(!idtoidfield->text().isEmpty())
  {
        rbSelected->setChecked(false);
        rbAll->setChecked(false);
        rbSelected->setCheckable(false);
        rbAll->setCheckable(false);
        rbSelected->update ();
        rbAll->update ();
  }
  else
  {
    rbSelected->setCheckable(true);
    rbAll->setCheckable(true);
  }
}
PL_Document* Wizzardexport::getView()
{
  switch(cbtypeofoutput->currentIndex())
  {
    case XML:
      return new PL_XmlDoc;
    case PDF:
      return new PL_PdfDoc;
    case PLS:
      return new PL_PlsDoc;
    case HTML:
      return new PL_HtmlDoc;
    case CVS:
      return new PL_CvsDoc;
  }
  return NULL;
}
QList<int>*  Wizzardexport::getMap()
{
  QList<int>* listint;
  if(rbscreen->isChecked())
  {
    listint= view->getVisibleColumn();
  }
  else
  {
    listint = new QList<int>;
        listofselectedfield->selectAll();
        QList<QListWidgetItem *> a= listofselectedfield->selectedItems();
        
        
        foreach(QListWidgetItem *b,a)
        {
        
        
        listint->append(SLlistcolumn.indexOf(b->text()));
        }
  }
  return  listint;
}

Pl_DocumentModel*  Wizzardexport::getModel()
{
  PL_ImplDocModel* model = new PL_ImplDocModel();
  if(rbAll->isChecked())
  {
    model->setList(Playlist::getInstance()->getP_myPlaylist());
  }
  else if(rbSelected->isChecked())
  {
    
    model->setList(view->getCurrentView()->getSelectedItem());
  }
  else
  {
    
    QRegExp rxlen("(\\d+)-(\\d+)");
    int pos = rxlen.indexIn(idtoidfield->text());
    int start=-1;
    int end=-1;
    if (pos > -1) 
    {
      start = rxlen.cap(1).toInt(); 
      end = rxlen.cap(2).toInt(); 
    }
    if(end<start)
    {
      
      return NULL;
    }
    else if((start>-1)&&(end<Playlist::getInstance()->getP_myPlaylist()->size()))
    {
     
      QList<PlaylistItem*>* list = new QList<PlaylistItem*>;
      for(;start<end;start++)
      {
        list->insert(start,Playlist::getInstance()->getP_myPlaylist()->at(start));
      }
      
      model->setList(list);
    }
  }
  
  return model;
}
