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
#ifndef DATA_H
#define DATA_H

#include <QStringList>
#include <QVariant>
#include <QHeaderView>
/**
 * \struct BitrateLayer
 * \brief all informations for the audio file bit rate 
*/
#define HAVE_PHONON

typedef struct BitrateLayer
{
  char Bitrate;           //bitrate
  char Layer;             //Type of Layer (I,II,III)
  char MPEG;              //Type of MPEG (1 or 2)
}LayerBitrate;


/**
 * \struct SongFields
 * \brief all supported informations form a playlist item.
 */
struct SongFields
{
  QString Title;
  int duration;
  QString Artist;
  int genre;
  QString album;
  QString Comment;
  int Year;
  int Bitrate;
  QString lyrics;
  int track;
  QImage m_image;
};

enum dataColumn{TITLE,ARTIST,TIME,YEAR,ALBUM,TRACK,GENRE,COMMENT,BITRATE,PICTURE};

 Q_DECLARE_METATYPE(dataColumn)
 static QStringList SLlistcolumn = (QStringList() << QObject::tr("TITLE") 
     <<QObject::tr("ARTIST")  << QObject::tr("TIME") <<QObject::tr("YEAR") 
     << QObject::tr("ALBUM") << QObject::tr("TRACK")<< QObject::tr("GENRE") <<QObject::tr("COMMENT")
     <<QObject::tr("BITRATE")<<QObject::tr("PICTURE"));
 
 static QString FileSupported = (QString(QObject::tr("MP3 media files (*.mp3)\nother media files (*.*)")));
 
 
typedef struct 
{
  dataColumn x;
  QVariant name;
  QHeaderView::ResizeMode resize;
  bool visible;
} headerlistview;

 Q_DECLARE_METATYPE(headerlistview)
 Q_DECLARE_METATYPE(QList<headerlistview*>)
//enum mediatype{MP3,OTHER};



enum TypeOfExport {XML,PLS,PDF,HTML,CVS};
enum ViewerBehaviour {ALWAYSSHOWN,ALWAYSHIDDEN,ASPREVIOUS};
static QStringList listTypeOfExport = (QStringList() <<QObject::tr("XML")<<QObject::tr("PLS")<<QObject::tr("PDF")<<QObject::tr("HTML")<<QObject::tr("CVS") );


#define EMPTY_SELECTION 100
#define MOVE_SELECTION 101
#define ADDED_SELECTION 102

static QStringList listgenre = (QStringList() <<QObject::tr("Blues")<<QObject::tr("Classic Rock")<<QObject::tr("Country")<<QObject::tr("Dance")
      <<QObject::tr("Disco")  <<QObject::tr("Funk")  <<QObject::tr("Grunge")  <<QObject::tr("Hip-Hop")
      <<QObject::tr("Jazz")  <<QObject::tr("Metal")  <<QObject::tr("New Age")  <<QObject::tr("Oldies")
      <<QObject::tr("Other")  <<QObject::tr("Pop")  <<QObject::tr("R&B")  <<QObject::tr("Rap")
      <<QObject::tr("Reggae")  <<QObject::tr("Rock")  <<QObject::tr("Techno")  <<QObject::tr("Industrial")
      <<QObject::tr("Alternative")  <<QObject::tr("Ska")  <<QObject::tr("Death Metal")  <<QObject::tr("Pranks")
      <<QObject::tr("Soundtrack")  <<QObject::tr("Euro-Techno")  <<QObject::tr("Ambient")  <<QObject::tr("Trip-Hop")
      <<QObject::tr("Vocal")  <<QObject::tr("Jazz+Funk")  <<QObject::tr("Fusion")  <<QObject::tr("Trance")
      <<QObject::tr("Classical")  <<QObject::tr("Instrumental")  <<QObject::tr("Acid")   <<QObject::tr("House")
      <<QObject::tr("Game")  <<QObject::tr("Sound Clip")  <<QObject::tr("Gospel")  <<QObject::tr("Noise")
      <<QObject::tr("AlternRock")  <<QObject::tr("Bass")  <<QObject::tr("Soul")  <<QObject::tr("Punk")
      <<QObject::tr("Space")  <<QObject::tr("Meditative")  <<QObject::tr("Instrumental Pop")  <<QObject::tr("Instrumental Rock")
      <<QObject::tr("Ethnic")  <<QObject::tr("Gothic")  <<QObject::tr("Darkwave")  <<QObject::tr("Techno-Industrial")
      <<QObject::tr("Electronic")  <<QObject::tr("Pop-Folk")  <<QObject::tr("Eurodance")  <<QObject::tr("Dream")
      <<QObject::tr("Southern Rock")  <<QObject::tr("Comedy")  <<QObject::tr("Cult")  <<QObject::tr("Gangsta")
      <<QObject::tr("Top40")  <<QObject::tr("Christian Rap")  <<QObject::tr("Pop/Funk")  <<QObject::tr("Jungle")
      <<QObject::tr("Native American")  <<QObject::tr("Cabaret")  <<QObject::tr("New Wave")  <<QObject::tr("Psychadelic")
      <<QObject::tr("Rave")  <<QObject::tr("Showtunes")  <<QObject::tr("Trailer")  <<QObject::tr("Lo-Fi")
      <<QObject::tr("Tribal")  <<QObject::tr("Acid Punk")  <<QObject::tr("Acid Jazz")  <<QObject::tr("Polka")
      <<QObject::tr("Retro")  <<QObject::tr("Musical")  <<QObject::tr("Rock & Roll")  <<QObject::tr("Hard Rock")
      <<QObject::tr("Folk")  <<QObject::tr("Folk-Rock")  <<QObject::tr("National Folk")  <<QObject::tr("Swing")
      <<QObject::tr("Fast Fusion")  <<QObject::tr("Bebob")  <<QObject::tr("Latin")  <<QObject::tr("Revival")
      <<QObject::tr("Celtic")  <<QObject::tr("Bluegrass")  <<QObject::tr("Avantgarde")  <<QObject::tr("Gothic Rock")
      <<QObject::tr("Progressive Rock")  <<QObject::tr("Psychedelic Rock")  <<QObject::tr("Symphonic Rock")  <<QObject::tr("Slow Rock")
      <<QObject::tr("Big Band")  <<QObject::tr("Chorus")  <<QObject::tr("Easy Listening")  <<QObject::tr("Acoustic")
      <<QObject::tr("Humour")  <<QObject::tr("Speech")  <<QObject::tr("Chanson")  <<QObject::tr("Opera")
      <<QObject::tr("Chamber Music")  <<QObject::tr("Sonata")  <<QObject::tr("Symphony")  <<QObject::tr("Booty Bass")
      <<QObject::tr("Primus")  <<QObject::tr("Porn Groove")  <<QObject::tr("Satire")  <<QObject::tr("Slow Jam")
      <<QObject::tr("Club")  <<QObject::tr("Tango")  <<QObject::tr("Samba")  <<QObject::tr("Folklore")
      <<QObject::tr("Ballad")  <<QObject::tr("Power Ballad")  <<QObject::tr("Rhythmic Soul")  <<QObject::tr("Freestyle")
      <<QObject::tr("Duet")  <<QObject::tr("Punk Rock")  <<QObject::tr("Drum Solo")  <<QObject::tr("A capella")
      <<QObject::tr("Euro-House")  <<QObject::tr("Dance Hall")  <<QObject::tr("Goa")  <<QObject::tr("Drum & Bass")
      <<QObject::tr("Club House")  <<QObject::tr("Hardcore")  <<QObject::tr("Terror")  <<QObject::tr("Indie")
      <<QObject::tr("BritPop")  <<QObject::tr("Negerpunk")  <<QObject::tr("Polsk Punk")  <<QObject::tr("Beat")
      <<QObject::tr("Christian gangsta rap")<<QObject::tr("Heavy metal")  <<QObject::tr("Black metal")  <<QObject::tr("Crossover")
      <<QObject::tr("Modern christian music")  <<QObject::tr("Christian Rock ")  <<QObject::tr("Merengue")  <<QObject::tr("Salsa")
      <<QObject::tr("Thrash metal")  <<QObject::tr("Anime")<<QObject::tr("JPop")  <<QObject::tr("Synthpop"));


#endif
