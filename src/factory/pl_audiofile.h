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
#ifndef PL_AUDIOFILE_H
#define PL_AUDIOFILE_H

#include "pl_mediafile.h"
#include <QString>
#include <QImage>
/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_AudioFile
 * \brief this class was only created to make a real oriented object architecture but it is not used.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo  REMOVE IT!!!!!!!!!!!
*/
class PL_AudioFile : public PL_MediaFile
{
public:
  PL_AudioFile(QString& uri);

    ~PL_AudioFile();

  virtual int getDuration() const =0;
  virtual const  QString& getTitle() const =0;
  virtual const QString& getArtist() const =0;
  virtual int getGenre() const =0;
  virtual const QString& getAlbumtitle() const =0;
  virtual const QString& getComment() const =0;
  virtual int getYear() const =0;
  virtual int getBitrate() const =0;
  virtual int getTrack() const =0;
  virtual const QImage& getPicture() const =0;

};

#endif
