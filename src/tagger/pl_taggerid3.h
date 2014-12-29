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
#ifndef PL_TAGGERID3_H
#define PL_TAGGERID3_H

#include <id3/tag.h>
#include <id3/misc_support.h>
#include <id3/utils.h>
#include <id3/readers.h>

#include <QString>
#include <QStringList>
#include "pl_taglibfile.h"
#define SIZE_DATA 1024
/**
 * \class PL_TaggerID3
 * \brief Class used for adapt the PlayListGenerator with Id3lib (mp3 file support). Must inherit from it to allow the use of new library.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known 
 * \warning no known 
 * \todo   no         
*/
class PL_TaggerID3 : public PL_TagLibFile
{
  ID3_Tag* myTaggger;
  QString* filename;
  static QStringList* listgenre;
  ID3_FrameID getIDFrame(int i);
  
  int nCbrBitRate, nVbrBitRate, nBitRate, nSampleRate, nLength;
  char* szBitRate;
  char* szMpegLayer;
  char* szMpegVersion;
  char* szChannelMode;
  const Mp3_Headerinfo* m_mp3header;
  
 public:
   PL_TaggerID3();
   PL_TaggerID3(QString* _filename);
   void setValue(DataField x,QVariant& data,bool replace);
  // static void initGenreList();
   virtual ~PL_TaggerID3();
   virtual QVariant getValue(int i);
   virtual QStringList* getgenres();
   bool readheader();
   const Mp3_Headerinfo* GetMp3HeaderInfo();
  
};

#endif
