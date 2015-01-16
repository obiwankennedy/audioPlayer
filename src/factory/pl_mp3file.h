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
#ifndef PL_MP3FILE_H
#define PL_MP3FILE_H

#include "pl_audiofile.h"
#include <pl_taggerid3.h>
#include <QFile>
#include <QString>
#include "../data.h"
#include "data/song.h"
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_Mp3File
 * \brief Implemented PL_AudioFile to manage mp3 files.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no        
*/
class PL_Mp3File : public PL_AudioFile
{
private:
    PL_TaggerID3* Mp3tagger;
 
 
    QString* uri;
    
    Song* fields;
    bool linked;
   const Mp3_Headerinfo* header;
public:
    PL_Mp3File();
    PL_Mp3File(QString& uri,Song* fields);
    ~PL_Mp3File();
    
    
    int getDuration() const;
    const QString& getTitle() const;
    const QString& getArtist() const;
    int getGenre() const;
    const QString& getAlbumtitle() const;
    const QString& getComment() const;
    int getYear() const;
    int getBitrate() const;
    int getTrack() const;
    const QImage& getPicture() const;

    void setTitle(QString p);
    void setArtist(QString p);
    void setGenre(int p);
    void setAlbumtitle(QString p);
    void setComment(QString p);
    void setYear(int p);
    void link();
    void setTrack(int p);
    
    bool is_linked();
    QStringList* getgenres();   
    void setValue(DataField x,QVariant& value,bool replace);
    void ForceTagReading();
    void parseHeader();
    virtual void readData(QDataStream & in);
    virtual void writting(QDataStream & out) const;
};

#endif
