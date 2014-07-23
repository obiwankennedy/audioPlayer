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
#include "xmlimport.h"
#include <QDomText>
#include <QDomDocument>
#include <QDomElement>

XmlImport::XmlImport()
 : ImportParser()
{
}


XmlImport::~XmlImport()
{
}
void XmlImport::readFile()
{
  
  QFile file(filename);
  /*if (!file.open(QFile::ReadOnly)) 
  {
   
    return;
  }*/

  QDomDocument doc;
  QString errorstr;
  int errorline;
  int errorcolumn;
  
  if(!doc.setContent(&file,true,&errorstr,&errorline,&errorcolumn))
  {

    
    return;
    
  }
  QDomElement root = doc.documentElement();
  if(root.tagName()!="playlist")
    return ;
  PlaylistItem* p;
  QDomNode node = root.firstChild();
  QDomNode mediatag;
  QString*  uri;
  
  while(!node.isNull())
  {
    if(node.toElement().tagName()=="file")
    {
      mediatag=node.firstChild();
      while(!mediatag.isNull())
      {
        
        if(mediatag.toElement().tagName()=="URI")
        {
          p= new PlaylistItem;
          uri = new QString;

          *uri= mediatag.toElement().text();
          p->setURI(*uri);
          
          result->append(p);
        }
        mediatag = mediatag.nextSibling();
      }
      
    }
    node = node.nextSibling();
  }
}

