#include "pl_taggerogg.h"
#include <QDebug>
#include <QFileInfo>
#include <QTextStream>
#include <taglib/attachedpictureframe.h>
#include <taglib/id3v1tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2tag.h>
#include <taglib/mp4tag.h>
#include <taglib/tlist.h>
#include <taglib/tpropertymap.h>
#include <taglib/tstring.h>
#include <taglib/vorbisfile.h>
#include <taglib/xiphcomment.h>
//

PL_TaggerOgg::PL_TaggerOgg() : PL_TagLibFile(), myTagggerFileMPG(NULL)
{
    // TODO
}
//

PL_TaggerOgg::PL_TaggerOgg(QString* _filename) : PL_TagLibFile(), myTagggerFileMPG(NULL)
{
    filename= _filename;
    // myTaggger = new TagLib::FileRef(filename->toStdString().c_str());
    myTaggger= new TagLib::FileRef(filename->toLocal8Bit());
    QFileInfo info(*filename);
    if(info.suffix() == "mp3")
    {
        myTagggerFileMPG= new TagLib::MPEG::File(filename->toLocal8Bit());
    }
}

PL_TaggerOgg::~PL_TaggerOgg()
{
    delete myTaggger;
}
void PL_TaggerOgg::close()
{
    if(myTaggger != NULL)
    {
        delete myTaggger;
        myTaggger= NULL;
    }
}

QVariant PL_TaggerOgg::getValue(int i)
{
    if(NULL == myTaggger->tag())
    {
        return QString();
    }

    switch(i)
    {
    case TITLE:
    {
        return QString(TStringToQString(myTaggger->tag()->title()));
    }
    case ARTIST:
    {
        return QString(TStringToQString(myTaggger->tag()->artist()));
    }
    case YEAR:
    {
        return myTaggger->tag()->year();
    }
    case ALBUM:
    {
        return QString(TStringToQString(myTaggger->tag()->album()));
    }
    case TIME:
    {
        // qDebug() << myTaggger->audioProperties()->length();// <<
        // //myTaggger->audioProperties()->lengthInSeconds();
        return myTaggger->audioProperties()->length();
    }
    case GENRE:
        return QString(TStringToQString(myTaggger->tag()->genre()));
    case COMMENT:
        return QString(TStringToQString(myTaggger->tag()->comment()));
    case TRACK:
    {
        return myTaggger->tag()->track();
    }

    case BITRATE:
        return QString(myTaggger->audioProperties()->bitrate());
    case PICTURE:
    {
        // qDebug() << "try to read picture";
        QImage image;
        if(NULL != myTagggerFileMPG)
        {
            TagLib::ID3v2::Tag* tag= dynamic_cast<TagLib::ID3v2::Tag*>(myTagggerFileMPG->ID3v2Tag());

            //  TagLib::ID3v1::Tag* tagv1=dynamic_cast<TagLib::ID3v1::Tag*>(myTaggger->tag());

            //  TagLib::MP4::Tag* tagMP4=dynamic_cast<TagLib::MP4::Tag*>(myTaggger->tag());

            //  TagLib::Ogg::XiphComment* tagOgg=dynamic_cast<TagLib::Ogg::XiphComment*>(myTaggger->tag());
            //            if(tagMP4!=NULL)
            //            {
            //                qDebug() << "file MP4";
            //            }
            //            if(tagOgg!=NULL)
            //            {
            //                qDebug() << "file tagOgg";
            //            }
            //            if(tagv1!=NULL)
            //            {
            //                qDebug() << "file ID3v1";
            //            }

            if(NULL != tag)
            {
                TagLib::ID3v2::FrameList frames= tag->frameList("APIC");

                if(frames.isEmpty())
                {
                    //  qDebug() << "No pictuer to read";
                    return image;
                }
                TagLib::ID3v2::AttachedPictureFrame* picFrame
                    = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frames.front());

                image.loadFromData((const uchar*)picFrame->picture().data(), picFrame->picture().size());

                //  qDebug() << "Picture has been found.";
            }
        }
        return image;
    }
    default:
        return QString("");
    }

    return QString("");
}
void PL_TaggerOgg::setValue(dataColumn x, QVariant& data, bool /*replace*/)
{
    if(NULL == myTaggger->tag())
        return;
    switch(x)
    {
    case TITLE:
        myTaggger->tag()->setTitle(TagLib::String(data.toString().toStdString(), TagLib::String::UTF8));
        break;
    case ARTIST:

        myTaggger->tag()->setArtist(TagLib::String(data.toString().toStdString(), TagLib::String::UTF8));
        break;
    case YEAR:
        myTaggger->tag()->setYear(data.toString().toInt());
        break;
    case ALBUM:
    {
        //   TagLib::Ogg::XiphComment* ab = (TagLib::Ogg::XiphComment*)myTaggger->tag();
        // ab->addField("TITLE",TagLib::String(data.toString().toStdString(),TagLib::String::UTF8));
        myTaggger->tag()->setAlbum(TagLib::String(data.toString().toStdString(), TagLib::String::UTF8));

        break;
    }
    case GENRE:
        myTaggger->tag()->setGenre(TagLib::String(data.toString().toStdString(), TagLib::String::UTF8));
        break;
    case COMMENT:
        myTaggger->tag()->setComment(TagLib::String(data.toString().toStdString(), TagLib::String::UTF8));
        break;
    case TRACK:
        myTaggger->tag()->setTrack(data.toString().toInt());
        break;
    case PICTURE:
    case TIME:
    case BITRATE:
        return;
    }

    myTaggger->save();
}

QStringList* PL_TaggerOgg::listgenre= NULL;

QStringList* PL_TaggerOgg::getgenres()
{
    return listgenre;
}

/* const Mp3_Headerinfo* PL_TaggerOgg::GetMp3HeaderInfo()
{
  return myTaggger->GetMp3HeaderInfo();
}*/
