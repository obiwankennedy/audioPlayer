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
#include "appcontroller.h"
#include "audiocontroller.h"
#include "audiofilemodel.h"

#include <QDebug>
#include <QFile>
#include <QQmlContext>
#include <QSettings>
#include <QUrl>

#include "worker/filereaderhelper.h"

AppController* AppController::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
{
    auto ctrl = new AppController(nullptr);
    qmlEngine->addImageProvider("album", ctrl->audioCtrl()->pictureProvider());
    return ctrl;
}

AppController::AppController(QObject* parent)
    : QObject(parent)
    , m_audioCtrl(new AudioController)
{
    connect(m_audioCtrl.get(), &AudioController::deviceIndexChanged, this, &AppController::deviceIndexChanged);
    connect(m_audioCtrl.get(), &AudioController::hasVideoChanged, this, &AppController::hasVideoChanged);
    connect(m_audioCtrl.get(), &AudioController::stateChanged, this, &AppController::stateChanged);
    loadSettings();
    if (!m_filename.isEmpty())
        loadFile();
}

QStringList AppController::recentFiles() const
{
    return m_recentFiles;
}

FilteredModel* AppController::filteredModel() const
{
    return m_audioCtrl->filteredModel();
}

AudioController* AppController::audioCtrl() const
{
    return m_audioCtrl.get();
}

AppController::~AppController()
{
    saveSettings();
}

QAbstractItemModel* AppController::model() const
{
    return m_audioCtrl->model();
}

AudioFileModel* AppController::audioModel() const
{
    return m_audioCtrl->model();
}

void AppController::resetData()
{
    m_audioCtrl->resetModel();
}

void AppController::setFilename(QString filename)
{
    if (m_filename == filename)
        return;

    m_filename = QUrl(filename).toLocalFile();
    qDebug() << m_filename << "filename";
    emit filenameChanged(m_filename);
}

void AppController::addToExport(int songIndex)
{
    auto model = audioModel();
    model->addToExport(songIndex);
}

void AppController::resetExport()
{
    auto model = audioModel();
    model->cleanExportList();
}

void AppController::exportList()
{
    FileReaderHelper::exportFileToDirectory(audioModel());
    resetExport();
}

void AppController::removeSelection()
{
    auto fmodel = filteredModel();
    if (fmodel->search().isEmpty())
        return;
    auto size = fmodel->rowCount();
    std::vector<int> idxs;
    auto model = audioModel();
    for (int i = 0; i < size; ++i) {
        auto sourceIndex = fmodel->mapToSource(fmodel->index(i, 0));
        idxs.push_back(sourceIndex.row());
    }
    std::sort(std::begin(idxs), std::end(idxs), std::greater<int>());
    model->removeSongs(idxs);
}

void AppController::setDeviceIndex(int index)
{
    m_audioCtrl->setDeviceIndex(index);
}

void AppController::loadFile()
{
    if (m_filename.endsWith("m3u"))
        FileReaderHelper::readM3u(m_filename, m_audioCtrl->model());
    else if (m_filename.endsWith("apl"))
        FileReaderHelper::readAudioList(m_filename, m_audioCtrl->model());

    m_recentFiles.prepend(m_filename);
    saveSettings();
}

void AppController::saveFile()
{
    if (!m_filename.endsWith(".apl"))
        m_filename.append(".apl");
    FileReaderHelper::writeAudioList(m_filename, m_audioCtrl->model());
    saveSettings();
}

void AppController::saveSettings()
{
    QSettings setting("AudioPlayer", "AudioPlayer");

    setting.setValue("recentFiles", m_recentFiles);
    setting.setValue("lastFile", m_filename);
    setting.setValue("lastPlayedSong", m_audioCtrl->songIndex());
}

void AppController::loadSettings()
{
    QSettings setting("AudioPlayer", "AudioPlayer");
    m_recentFiles = setting.value("recentFiles").toStringList();
    m_filename = setting.value("lastFile").toString();
    auto songIdx = setting.value("lastPlayedSong").toInt();
    m_audioCtrl->setSongIndex(songIdx);
}

void AppController::addFiles(const QList<QUrl>& files, int idx)
{
    std::vector<QString> list;
    std::transform(files.begin(), files.end(), std::back_inserter(list),
        [](const QUrl& path) { return path.toLocalFile(); });
    auto model = m_audioCtrl->model();
    model->insertSongAt(idx, list);
}

void AppController::addDirectory(int idx, const QString& url)
{
    auto vec = FileReaderHelper::findAllAudioFiles(QUrl(url).toLocalFile());
    auto model = m_audioCtrl->model();
    model->insertSongAt(idx, vec);
}

QAbstractItemModel* AppController::outputModel() const
{
    return m_audioCtrl->devices();
}

int AppController::deviceIndex() const
{
    return m_audioCtrl->deviceIndex();
}

bool AppController::hasVideo() const
{
    return m_audioCtrl->hasVideo();
}
