/***************************************************************************
 *	Copyright (C) 2020 by Renaud Guezennec                               *
 *   http://www.rolisteam.org/contact                                      *
 *                                                                         *
 *   This software is free software; you can redistribute it and/or modify *
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
#include "filereaderhelper.h"

#include <QBuffer>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QString>
#include <QTextStream>

#include "audiofilemodel.h"

FileReaderHelper::FileReaderHelper() {}

void FileReaderHelper::readM3u(const QString& filename, AudioFileModel* model)
{
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "error text" << filename;

    QTextStream stream(&file);

    QList<QVariantMap> vec;
    while(!stream.atEnd())
    {
        QString uri, ext;
        ext= stream.readLine();
        uri= stream.readLine();
        QString title;
        int duration= 0;
        QString artist;
        QString album;
        vec.append(
            QVariantMap({{"path", uri}, {"title", title}, {"artist", artist}, {"album", album}, {"time", duration}}));
    }
    model->appendSongs(vec);
}

void FileReaderHelper::writeAudioList(const QString& filename, AudioFileModel* model)
{
    auto songs= model->songs();
    QJsonObject mainObj;
    QJsonArray array;
    for(auto song : songs)
    {
        QJsonObject obj;
        obj["path"]= song->m_filepath;
        obj["title"]= song->m_title;
        obj["artist"]= song->m_artist;
        obj["album"]= song->m_album;
        obj["time"]= static_cast<long long int>(song->m_time);
        array.append(obj);
    }

    auto images= model->dataImage();
    auto keys= images->keys();
    QJsonArray imgArray;
    for(auto const& key : qAsConst(keys))
    {
        auto value= images->value(key);
        if(value.isNull())
            continue;
        QJsonObject obj;
        obj["key"]= key;
        QByteArray array;
        QBuffer buffer(&array);
        buffer.open(QIODevice::WriteOnly);
        value.save(&buffer, "jpeg");
        obj["img"]= QString::fromUtf8(array.toBase64());
        imgArray.append(obj);
    }
    mainObj["songs"]= array;
    mainObj["images"]= imgArray;

    QJsonDocument doc(mainObj);

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "error saving";
    }
    file.write(doc.toJson());
}

void FileReaderHelper::readAudioList(const QString& filename, AudioFileModel* model)
{
    qDebug() << filename;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "error text" << filename;

    QJsonDocument doc= QJsonDocument::fromJson(file.readAll());

    auto mainObj= doc.object();

    auto array= mainObj["songs"].toArray();
    QList<QVariantMap> vec;
    for(auto const& value : qAsConst(array))
    {
        auto obj= value.toObject();
        vec.append(QVariantMap({{"path", obj["path"].toString()},
                                {"title", obj["title"].toString()},
                                {"artist", obj["artist"].toString()},
                                {"album", obj["album"].toString()},
                                {"time", obj["time"].toInt()}}));
    }

    auto images= model->dataImage();
    auto imgarray= mainObj["images"].toArray();
    for(auto const& imageObjRef : qAsConst(imgarray))
    {
        auto obj= imageObjRef.toObject();

        auto key= obj["key"].toString();
        auto data= QImage::fromData(QByteArray::fromBase64(obj["img"].toString().toUtf8()));
        images->insert(key, data);
    }

    model->appendSongs(vec);
}

std::vector<QString> FileReaderHelper::findAllAudioFiles(const QString& dir)
{
    std::vector<QString> vec;
    QDir direct(dir);
    auto list= direct.entryList(QStringList() << "*.mp3"
                                              << "*.mpc"
                                              << "*.wav"
                                              << "*.wma"
                                              << "*.flac"
                                              << "*.ogg",
                                QDir::Files);
    for(const QString &s : list)
    {
        vec.push_back(direct.absoluteFilePath(s));
    }

    for(const QString &p : direct.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        auto vec1= findAllAudioFiles(direct.absoluteFilePath(p));
        vec.insert(vec.end(), vec1.begin(), vec1.end());
    }

    return vec;
}

void FileReaderHelper::exportFileToDirectory(AudioFileModel* model)
{
    auto vec= model->exportList();
    QStringList songPaths;
    for(auto index : vec)
    {
        auto songInfo= model->songInfoAt(index);

        songPaths << songInfo->m_filepath;
    }
    // songPaths.append("www:/home/www/rolisteam/blog/file/export_music/");
    songPaths.append("/home/renaud/music/");
    QProcess proc;
    proc.start("cp", songPaths);
    if(!proc.waitForFinished())
        return;

    /*for(const auto& song : qAsConst(songPaths))
    {
        qDebug() << QString("http://blog.rolisteam.org/file/export_music/%1").arg(song);
    }*/
}
