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

/**
	@author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \class PL_AudioFile
 * \brief this class was only created to make a real oriented object architecture but it does not use.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no          
*/
class PL_AudioFile : public PL_MediaFile
{
public:
  PL_AudioFile(QString& uri);

    ~PL_AudioFile();

  virtual int getDuration() =0;
  virtual QString* getTitle() =0;
  virtual QString* getArtist() =0;
  virtual int getGenre() =0;
  virtual QString* getAlbumtitle() =0;
  virtual QString* getComment() =0;
  virtual int getYear() =0;
  virtual int getBitrate() =0;
  virtual int getTrack() =0;
  virtual QImage& getPicture() =0;

};

#endif
