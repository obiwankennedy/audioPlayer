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
#include "../document/pl_plsdoc.h"
#include <QMessageBox>
#include <QTextStream>
PL_PlsDoc::PL_PlsDoc()
 : PL_Document()
{
}


PL_PlsDoc::~PL_PlsDoc()
{
}

void PL_PlsDoc::write()
{
  
  QFile file(*filename);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(NULL, QObject::tr("PlaylistGenerator"),
                         QObject::tr("Cannot write file %1:\n%2.")
                             .arg(*filename)
                             .arg(file.errorString()));
    return;
  }

  QTextStream pls(&file);
  
  pls <<"[playlist]\nNumberOfEntries="<<model->rowCount()<< "\n\n";
  
  
  //map->clear()
  
  
  
  

   
   
   
   
   
    for(int i = 0; i<model->rowCount();i++)
    {
      
      
      pls << "File"<<i+1<<"="<< model->getUri(i) << "\n";
      pls << "Title"<<i+1<<"="<< model->getData(i,TITLE).toString() << "\n";
      pls << "Length"<<i+1<<"="<< model->getData(i,TIME).toString() << "\n\n";
      /*File1=http://streamexample.com:80
          Title1=My Favorite Online Radio
          Length1=-1
      */
    }  
    pls << "Version=2"<< endl;
  
  
}
