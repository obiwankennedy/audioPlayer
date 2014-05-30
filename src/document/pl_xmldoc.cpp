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
#include "../document/pl_xmldoc.h"
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>
#include <QDomText>
#include <QMessageBox>


PL_XmlDoc::PL_XmlDoc()
 : PL_Document()
{
}


PL_XmlDoc::~PL_XmlDoc()
{
}

void PL_XmlDoc::write()
{
  QDomDocument doc;
  QDomElement root = doc.createElement("playlist");
  
  
  
  
  
  
  QFile xmlfile(*filename);
  if (!xmlfile.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(NULL, QObject::tr("PlaylistGenerator"),
                         QObject::tr("Cannot write file %1:\n%2.")
                             .arg(*filename)
                             .arg(xmlfile.errorString()));
    return;
  }



  
  
  
  
  
  
  
  if(model!=NULL)
  {

   

  
   
   
   
    QDomElement file; 
   QDomElement field;
   QDomText data;
    for(int i = 0; i<model->rowCount();i++)
    {
      file = doc.createElement("file");
      for(int j = 0;j<map->size();j++)
      {

            field =  doc.createElement(model->getHeaderData(map->at(j)).toString().remove(QChar(' '))) ;
        
        
        field.appendChild(doc.createTextNode(model->getData(i,map->at(j)).toString()));
        
        file.appendChild(field);
      }
      field =  doc.createElement("URI") ;
        
        
      field.appendChild(doc.createTextNode(model->getUri(i)));
        
      file.appendChild(field);
      
        root.appendChild(file);
    }  
    doc.appendChild(root);
    QTextStream xml(&xmlfile);
    
    doc.save(xml,INDENT);
    
    
  }

}
