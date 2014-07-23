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
#include "../document/pl_htmldoc.h"
#include <QMessageBox>
#include <QTextStream>

PL_HtmlDoc::PL_HtmlDoc()
  : PL_Document()
{
  model=NULL;
  filename=NULL;
}


PL_HtmlDoc::~PL_HtmlDoc()
{
  
}

void PL_HtmlDoc::write()
{
  
  QFile file(*filename);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(NULL, QObject::tr("PlaylistGenerator"),
                         QObject::tr("Cannot write file %1:\n%2.")
                             .arg(*filename)
                             .arg(file.errorString()));
    return;
  }

  QTextStream html(&file);
  
  html << QObject::tr("<?xml version=\"1.0\"?>\n")
      << QObject::tr("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n")
      << QObject::tr("\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n")
      << QObject::tr("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n")
      << QObject::tr("<head><meta http-equiv=\"Content-Type\" content=\"text/html;  charset=utf-8\" />\n")
      << QObject::tr("<meta name=\"Author\" content=\"PlayList Generator\" />\n")
      << QObject::tr("<meta name=\"Description\" content=\"Auto-Generate Document\" />\n")
      << QObject::tr("<title></title></head><body>\n");
  
  
  
  
  
  
  
 if(model!=NULL)
 {
   html << "<table>"<< endl;
   
   html<< "<tr>";
   for(int k = 0;k<map->size();k++)
   {
     
     html<< "<td>" << model->getHeaderData(map->at(k)).toString() << "</td>";
     
   }
   html << "</tr>"<< endl;
   
   
   
   
   
   for(int i = 0; i<model->rowCount();i++)
   {
     html<< "<tr>";
     for(int j = 0;j<map->size();j++)
    {
      html<< "<td>" << model->getData(i,map->at(j)).toString() << "</td>";
    }
    html << "</tr>"<< endl;
   }  
   html << "</table>"<< endl;
 }
 html << "</body></html>";
}

