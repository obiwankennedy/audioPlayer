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
#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include "visitormedia.h"
#include "playlist.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class Thread
 * \brief Class to create a thread to make a parallel statement.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo must be use in many more statement and allow the communication to display a progress bar.                    
*/
class Thread : public QThread
{
  Q_OBJECT
public:
  Thread(QList<PlaylistItem*>* list);

    ~Thread();
    void setVisitor(VisitorMedia* visit);
    void stop();
    
  protected:
    void run();
  private:
    volatile bool stopped;
    VisitorMedia* visit;
    QList<PlaylistItem*>* list;
    QMutex mutex;
};

#endif
