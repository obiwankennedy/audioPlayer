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
#ifndef PL_DEFAULTAUDIO_H
#define PL_DEFAULTAUDIO_H

#include <pl_audiofile.h>
#include <data.h>
#include "data/song.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_DefaultAudio
 * \brief Implementation of PL_AudioFile to represent all not supported files. 
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no               
*/
class PL_DefaultAudio : public PL_AudioFile
{
   // Q_OBJECT

  QString* uri;
  Song* fields;

public:
  PL_DefaultAudio(QString& uri,Song* fields);
  
    ~PL_DefaultAudio();
    
    int getDuration() const;
    const QString& getTitle() const ;
    const QString& getArtist()const;
    int getGenre()const;
    const QString& getAlbumtitle()const;
    int getBitrate()const;
    const QString& getComment()const;
    int getYear()const;
    int getTrack()const;
    virtual const QImage& getPicture()const;
    
    void setTitle(QString p);
    void setArtist(QString p);
    void setGenre(int p);
    void setAlbumtitle(QString p);
    void setYear(int p);
    void setComment(QString p);
    void setTrack(int p);


    void setValue(DataField x,QVariant& value,bool replace);
    void ForceTagReading();
    
    virtual void readData(QDataStream & in);
    virtual void writting(QDataStream & out) const;

/*private slots:
       void setMetaData();*/
};

#endif
