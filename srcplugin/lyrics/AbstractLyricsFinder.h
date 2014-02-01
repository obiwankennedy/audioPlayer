/***************************************************************************
 *   Copyright (C) 2009 by Renaud Guezennec   *
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
#ifndef ABSTRACTLYRICSFINDER_H
#define ABSTRACTLYRICSFINDER_H

#include <data.h>
#include <QString>
class AbstractLyricsFinder : public QObject
{
    Q_OBJECT
protected:
    QString* m_lyrics;
    bool m_isFound;
public:
    virtual void setfields(const SongFields * s) = 0;
    virtual void search() = 0;
    virtual QString* GetLyrics() = 0;
    virtual bool foundLyrics() =0;
signals:
    void lyricsready();

};


#endif // ABSTRACTLYRICSFINDER_H
