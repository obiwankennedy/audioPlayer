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
#include "pl_directoryfacade.h"

PL_directoryFacade::PL_directoryFacade()
{
    dirpath= NULL;
    p= new VisitorFinder;
}

PL_directoryFacade::PL_directoryFacade(QString _dirpath) : dirpath(NULL)
{
    dirpath= &_dirpath;
    p= new VisitorFinder;
}

PL_directoryFacade::~PL_directoryFacade()
{
    delete p;
}

QList<PlaylistItem*>* PL_directoryFacade::browseDir()
{
    Directory mydir(*dirpath);
    mydir.acceptVisitor(p);

    return p->getItemlist();
}
