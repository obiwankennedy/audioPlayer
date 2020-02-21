/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec                                *
 *   renaud.guezennec@gmail.com                                            *
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
#include "playlistitem.h"
#include "itemdecorator.h"
#include <QDebug>
#include <QTextStream>

PlaylistItem::PlaylistItem() : uri(NULL), ext(NULL), myfile(NULL)
{
    fields= new SongFields;
    facade= MediaFacade::getInstance();
    fields->genre= -1;
    fields->duration= -1;
    fields->Bitrate= -1;
    fields->Year= -1;
    urichanged= false;
    qRegisterMetaTypeStreamOperators<PlaylistItem>("PlaylistItem");
}

PlaylistItem* PlaylistItem::Readingitem= NULL;

PlaylistItem::~PlaylistItem()
{
    facade= NULL;
    delete fields;
    delete myfile;
    delete uri;
    delete ext;
}

PlaylistItem::PlaylistItem(const PlaylistItem& original)
{
    this->facade= MediaFacade::getInstance();
    this->myfile= NULL;

    this->fields= new SongFields;
    this->fields->Title= original.fields->Title;
    this->fields->Artist= original.fields->Artist;
    this->fields->genre= original.fields->genre;
    this->fields->album= original.fields->album;
    this->fields->duration= original.fields->duration;
    this->fields->Bitrate= original.fields->Bitrate;
    this->fields->Comment= original.fields->Comment;
    this->fields->Year= original.fields->Year;
    this->fields->m_image= original.fields->m_image;

    this->ext= new QString();
    this->uri= new QString();

    if(NULL != original.uri)
    {
        *this->uri= *original.uri;
    }

    if(NULL != original.ext)
    {
        *this->ext= *original.ext;
    }

    findmedia();
}
// MediaFacade *PlaylistItem::facade = NULL;
QString PlaylistItem::getReadableTitle()
{
    return QString("%1 - %2").arg(this->fields->Artist).arg(this->fields->Title);
}
const QString PlaylistItem::getURI() const
{
    if(uri == NULL)
    {
        return QString();
    }

    return *uri;
}
QImage& PlaylistItem::getPicture()
{
    fields->m_image= getKey()->getMember(PICTURE).value<QImage>();

    return fields->m_image;
}

void PlaylistItem::setURI(QString& p)
{
    if(uri == NULL)
        uri= new QString;
    if(ext == NULL)
        ext= new QString;
    *uri= p;
    urichanged= true;
    findmedia();
}

void PlaylistItem::findmedia()
{
    if((myfile == NULL) || (urichanged))
    {
        exploseExt();
        myfile= facade->buildaMedia(*uri, key, fields);
        key->setItem(this);
    }
}
QString PlaylistItem::toString()
{
    if((fields->Title.isNull()))
        fields->Title= getKey()->getMember(TITLE).toString();
    if((fields->Artist.isNull()))
        fields->Artist= getKey()->getMember(ARTIST).toString();

    return QString(fields->Artist + " - " + fields->Title);
}
const QString PlaylistItem::getExt() const
{
    if(ext == NULL)
        return QString();

    return *ext;
}
void PlaylistItem::SetExt(QString& p)
{
    ext= &p;
    exploseExt();
}

void PlaylistItem::buildExt()
{
    int a;

    if(ext == NULL)
    {
        ext= new QString;
    }
    if(fields->duration == -1)
        a= 0;
    else
        a= fields->duration;
    a/= 1000;

    if((fields->Title.isNull()))
        /* *fields->Title=*/getKey()->getMember(TITLE).toString();
    if((fields->Artist.isNull()))
        /* *fields->Artist=*/getKey()->getMember(ARTIST).toString();

    (*ext)= "#EXTINF:" + QString::number(a) + "," + fields->Artist.simplified() + " - " + fields->Title.simplified();
}
void PlaylistItem::exploseExt()
{
    if((ext != NULL) && (!ext->isEmpty()))
    {
        QStringList a= ext->split(':');
        if(a.size() == 2)
        {
            a= a[1].split(',');
            if(a.size() == 2)
            {
                bool ok;
                int tmptime= a[0].toInt(&ok, 10);
                if(ok)
                    fields->duration= (tmptime);

                a= a[1].split("- ");
                if(a.size() == 2)
                {
                    (fields->Title)= a[1].simplified();

                    (fields->Artist)= a[0].simplified();
                }
            }
        }
    }
    ext= NULL;
}
PL_MediaFile* PlaylistItem::getMediaFile()
{
    return myfile;
}

ItemDecorator* PlaylistItem::getKey() const
{
    return key;
}
const SongFields* PlaylistItem::getFields()
{
    return fields;
}
SongFields* PlaylistItem::getFields2()
{
    return fields;
}
void PlaylistItem::ForceTagReading()
{
    key->setItem(this);
    key->ForceTagReading();
}
bool PlaylistItem::isReading() const
{
    return (Readingitem == this);
}
void PlaylistItem::setReading(bool t)
{
    if(t)
        Readingitem= this;
}
QTextStream& operator<<(QTextStream& Out, const PlaylistItem& B)
{
    Out << B.getExt() << endl;
    Out << B.getURI() << endl;

    return Out;
}

QTextStream& operator>>(QTextStream& is, PlaylistItem& B)
{
    QString* a= new QString();

    B.uri= new QString();

    (*a)= is.readLine();
    if(!a->startsWith("#EXTINF", Qt::CaseSensitive))
    {
        B.uri= a;
        B.ext= new QString();
    }
    else
    {
        B.uri= new QString();
        B.ext= a;
        (*B.uri)= is.readLine();
    }
    B.findmedia();
    return is;
}

QDataStream& operator<<(QDataStream& Out, const PlaylistItem& B)
{
    Out << B.getExt();
    Out << B.getURI();

    Out << (*B.myfile);

    return Out;
}

QDataStream& operator>>(QDataStream& is, PlaylistItem& B)
{
    B.ext= new QString;
    B.uri= new QString;
    is >> (*B.ext);
    is >> (*B.uri);

    // qDebug() <<( *B.uri) << endl;
    B.findmedia();
    is >> (*B.myfile);

    /*B.fields->Artist = new String;
    is >> (*B.fields->Artist) ;
    is >> (*B.fields->Title) ;
    is >> (B.fields->genre) ;
    is >> (B.fields->duration) ;
    is>> (B.fields->Bitrate) ;
    is >> (*B.fields->Comment);
    is >> (B.fields->Year) ;*/

    return is;
}
