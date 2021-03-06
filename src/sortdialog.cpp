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
#include "sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
  : QDialog(parent )
{
  setupUi(this);
  column->addItems(SLlistcolumn);
  Acen->setChecked(true);
}


SortDialog::~SortDialog()
{
}

dataColumn SortDialog::getColunm()
{
  switch(column->currentIndex())
  {
    case TITLE:
      return TITLE;
    case ARTIST:
      return ARTIST;
    case TIME:
      return TIME;
    case ALBUM:
      return ALBUM;
    case GENRE:
      return GENRE;
    case BITRATE:
      return BITRATE;
    case YEAR:
      return YEAR;
    case COMMENT:
      return COMMENT;
    default:
      return TITLE;
  }
  
}
Qt::SortOrder SortDialog::getOrder()
{
  if(!Acen->isChecked())
    return Qt::DescendingOrder;
  else
   return Qt::AscendingOrder;
}
