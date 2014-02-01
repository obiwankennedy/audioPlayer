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
#ifndef PL_MEDIAFILE_H
#define PL_MEDIAFILE_H

#include <QString>
#include "../directoryFacade/file.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_MediaFile
 * \brief abstract class to represent a media file.
 * \version 1.0
 * \date 22/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no        
*/
class PL_MediaFile : public File
{
protected:
  int mode;
public:
  PL_MediaFile(QString& uri);
    virtual ~PL_MediaFile();
    
    virtual int getDuration()=0;
    virtual QString* getTitle()=0;
    virtual QString* getArtist()=0;
    virtual int getGenre()=0;
    virtual QString* getAlbumtitle()=0;
    virtual QString* getComment()=0;    
    virtual int getYear()=0;   
    virtual int getBitrate()=0;
    virtual int getTrack()=0;
    
    virtual void PreReading();

    virtual void setTitle(QString p)=0;
    virtual void setArtist(QString p)=0;
    virtual void setGenre(int p)=0;
    virtual void setYear(int p)=0;
    virtual void setComment(QString p)=0;
    virtual void setAlbumtitle(QString p)=0;
    virtual void setTrack(int p)=0;

    virtual void ForceTagReading()=0;
    
    virtual void readering(QDataStream & in)=0;
    virtual void writting(QDataStream & out) const =0;
    
    friend QDataStream& operator<<(QDataStream& os,const PL_MediaFile&);
    friend QDataStream& operator>>(QDataStream& is,PL_MediaFile&);
};

#endif
