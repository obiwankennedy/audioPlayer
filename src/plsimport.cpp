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
#include "plsimport.h"

PLSimport::PLSimport()
 : ImportParser()
{
}


PLSimport::~PLSimport()
{
  
}
void PLSimport::readFile()
{ 
 
  QFile file(filename);
  if (!file.open(QFile::ReadOnly)) {
   
    return;
  }

  QTextStream is(&file);
  
  PlaylistItem* p;
 // QString* duration;
 // QString* title;
  QString* uri; 
  QRegExp rxlen("=");
  QRegExp rxlen2("(\\d+)");
  int pos=-1;
  
  is.readLine();

  int i = rxlen2.indexIn(is.readLine());
  if(i>-1)
    i = rxlen2.cap(1).toInt();

  is.readLine();

for(int j = 0 ;j<i;j++)
{
  p= new PlaylistItem;

    uri = new QString;

    *uri  = is.readLine();

    pos = rxlen.indexIn(*uri);
    
    if (pos > -1) 
    {
      uri->remove(0, pos+1);

    }
   
    
    is.readLine();

    
    
    is.readLine();

    
    is.readLine();

    p->setURI(*uri);
    result->append(p);
  }
}
