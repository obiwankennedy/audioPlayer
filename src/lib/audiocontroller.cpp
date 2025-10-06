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
#include "audiocontroller.h"

#include "audiofilemodel.h"
#include "commandserver.h"
#include <QAudioDevice>
#include <QMediaDevices>
#include <QMediaMetaData>
#include <random>

typedef void (*PtrFunct)(int);

AudioController* sCtrl { nullptr };

void show(int i)
{
    sCtrl->display(i);
}

AudioController::AudioController(QObject* parent)
    : QObject(parent)
    , m_model(new AudioFileModel)
    , m_filteredModel(new FilteredModel)
    , m_filterTagModel(new TagFilteredModel)
    , m_pictureProvider(new AlbumPictureProvider())
    , m_player(new QMediaPlayer)
    , m_audioOutput(new QAudioOutput)
    , m_devices(new DeviceModel)
    , m_tagsModel(new TagModel)
{
    sCtrl = this;
    m_player->setAudioOutput(m_audioOutput.get());

    connect(m_player.get(), &QMediaPlayer::playbackStateChanged, this, &AudioController::stateChanged);
    auto const& devicesList = QMediaDevices::audioOutputs();
    m_deviceIndex = devicesList.indexOf(QMediaDevices::defaultAudioOutput());
    QStringList deviceNameList;
    deviceNameList.reserve(devicesList.size());
    std::transform(std::begin(devicesList), std::end(devicesList), std::back_inserter(deviceNameList), [](const QAudioDevice& device) {
        return device.description();
    });

    auto updateList = [this]() {
        auto const& devicesList = QMediaDevices::audioOutputs();
        QStringList deviceNameList;
        deviceNameList.reserve(devicesList.size());
        std::transform(std::begin(devicesList), std::end(devicesList), std::back_inserter(deviceNameList), [](const QAudioDevice& device) {
            return device.description();
        });
        m_devices->setDeviceList(deviceNameList);
    };

    auto mediaDevice = new QMediaDevices(this);
    connect(mediaDevice, &QMediaDevices::audioOutputsChanged, m_devices.get(), updateList);
    connect(m_player.get(), &QMediaPlayer::audioOutputChanged, m_devices.get(), updateList);
    updateList();

    connect(m_audioOutput.get(), &QAudioOutput::volumeChanged, this, &AudioController::volumeChanged);
    connect(m_player.get(), &QMediaPlayer::positionChanged, this, &AudioController::seekChanged);

    auto updateMetaData = [this]() {
        auto meta = m_player->metaData();

        auto keys = meta.keys();
        //auto tracks = m_player->audioTracks();

        if (keys.contains(QMediaMetaData::CoverArtImage)) {
            auto img = meta.value(QMediaMetaData::CoverArtImage);
            m_pictureProvider->setCurrentImage(img.value<QImage>(), title());
        } else if (keys.contains(QMediaMetaData::ThumbnailImage)) {
            auto img = meta.value(QMediaMetaData::ThumbnailImage);
            m_pictureProvider->setCurrentImage(img.value<QImage>(), title());
        } else {
            m_pictureProvider->setCurrentImage({}, {});
        }

        emit albumArtChanged();
    };
    connect(m_player.get(), &QMediaPlayer::metaDataChanged, this, updateMetaData);
    connect(m_player.get(), &QMediaPlayer::tracksChanged, this, updateMetaData);
    connect(m_player.get(), &QMediaPlayer::activeTracksChanged, this, updateMetaData);
    connect(m_player.get(), &QMediaPlayer::hasVideoChanged, this, &AudioController::hasVideoChanged);
    connect(m_player.get(), &QMediaPlayer::videoOutputChanged, this, &AudioController::videoOutputChanged);

    connect(m_player.get(), &QMediaPlayer::durationChanged, this, &AudioController::durationChanged);
    connect(m_player.get(), &QMediaPlayer::mediaStatusChanged, this, &AudioController::mediaStatus);

    m_filterTagModel->setSourceModel(m_model.get());
    m_filteredModel->setSourceModel(m_filterTagModel.get());
    //m_filteredModel->setSourceModel(m_model.get());
}

int AudioController::songIndex() const
{
    auto it = m_previousIndex.rbegin();
    it += m_pos;

    if (it == m_previousIndex.rend())
        return 0;

    return (*it);
}

AudioController::~AudioController() = default;

void AudioController::mediaStatus(QMediaPlayer::MediaStatus status)
{
    auto updateImage = [this]() {

    };

    switch (status) {
    case QMediaPlayer::EndOfMedia:
        next();
        break;
    case QMediaPlayer::BufferedMedia:
        updateImage();
        break;
    case QMediaPlayer::LoadedMedia:
        updateImage();
        break;
    default:
        break;
    }

    emit playingChanged();
}

void AudioController::next()
{
    if (m_pos > 0) {
        m_pos--;
        updateContent();
        play();
        emit songIndexChanged();
    } else {
        switch (m_mode) {
        case LOOP:
            repeatSong();
            break;
        case UNIQUE:
            break;
        case NEXT:
            nextInLineSong();
            break;
        case SHUFFLE:
            shuffleSong();
            break;
        }
    }
}

void AudioController::pause()
{
    m_player->pause();
}

void AudioController::previous()
{
    m_pos++;
    if (m_pos >= static_cast<int>(m_previousIndex.size()))
        m_pos = m_previousIndex.size() - 1;
    updateContent();
    play();
    emit songIndexChanged();
}
void AudioController::repeatSong()
{
    play();
}

void AudioController::nextInLineSong()
{
    auto it = m_previousIndex.rbegin();
    auto val = (*it) + 1;
    if(val >= m_filterTagModel->rowCount())
        return;
    setSongIndex(val);
    play();
}
void AudioController::shuffleSong()
{
    static auto seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 rng(seed1);
    auto r = m_filterTagModel->rowCount() - 1;

    std::uniform_int_distribution<qint64> dist(0, r);
    auto index = static_cast<int>(dist(rng));
    qDebug() << "shuffle song:"<<m_filterTagModel->rowCount() << index << m_filterTagModel->songIndexToSource(index);
    setSongIndex(m_filterTagModel->songIndexToSource(index));
    play();
}

void AudioController::resetModel() const
{
    m_model->resetModel();
}

QString AudioController::songImage() const
{
    QString res;
    auto info = m_model->songInfoAt(songIndex());

    if (info && !info->m_album.isEmpty() && !info->m_artist.isEmpty())
        res = QString("%1-%2").arg(info->m_artist, info->m_album);

    auto data = m_model->dataImage();
    if (data->contains(res))
        res = QString();
    return res;
}

AlbumPictureProvider* AudioController::pictureProvider() const
{
    return m_pictureProvider.get();
}

QString AudioController::albumArt() const
{
    return m_pictureProvider->id();
}

DeviceModel* AudioController::devices() const
{
    return m_devices.get();
}

void AudioController::display(int i)
{
    // qDebug() << "timer:" << i;
}

void AudioController::setContentData(const QByteArray& data)
{
    qDebug() << "setContent data" << data;
    m_buffer.close();
    m_buffer.setBuffer(nullptr);
    m_data.release();
    m_data.reset(new QByteArray(data));

    m_buffer.setBuffer(m_data.get());
    m_buffer.open(QIODevice::ReadOnly);
    m_player->setSourceDevice(&m_buffer, m_content);
    m_player->play();
}

void AudioController::addTag(const QString &tag)
{

    m_model->addTag(tag );//m_filterTagModel->songIndexToSource(songIndex)
}

void AudioController::refreshMetaData()
{
    m_model->refreshMetaData();
}
#include <QFileInfo>
void AudioController::removeFile(int index, bool onDisk)
{
    if(onDisk)
    {
        auto song = m_model->songInfoAt(index);
        QFileInfo info(song->m_filepath);
        if(info.exists())
        {
            QFile::moveToTrash(song->m_filepath);
        }
    }
    m_model->removeSongs({index});
}

void AudioController::setDeviceIndex(int index)
{
    if (index < 0 || m_deviceIndex == index)
        return;

    auto const& devicesList = QMediaDevices::audioOutputs();

    if (index >= devicesList.size())
        return;

    m_deviceIndex = index;
    m_audioOutput->setDevice(devicesList[index]);
    emit deviceIndexChanged();
}

int AudioController::deviceIndex() const
{
    return m_deviceIndex;
}

QUrl AudioController::content() const
{
    return m_content;
}

bool AudioController::hasVideo() const
{
    return m_player->hasVideo();
}

FilteredModel* AudioController::filteredModel() const
{
    return m_filteredModel.get();
}

AudioController::PlayingMode AudioController::mode() const
{
    return m_mode;
}

float AudioController::volume() const
{
    return m_audioOutput->volume();
}

qint64 AudioController::seek() const
{
    return m_player->position();
}

qint64 AudioController::duration() const
{
    return m_player->duration();
}

AudioFileModel* AudioController::model() const
{
    return m_model.get();
}

void AudioController::find(const QString& text)
{
    m_filteredModel->setSearch(text);
}

void AudioController::updateAudioDevices()
{
    auto const& devicesList = QMediaDevices::audioOutputs();
    QStringList deviceNameList;
    deviceNameList.reserve(devicesList.size());
    std::transform(std::begin(devicesList), std::end(devicesList), std::back_inserter(deviceNameList), [](const QAudioDevice& device) {
        return device.description();
    });
    m_devices->setDeviceList(deviceNameList);
}

QString AudioController::title() const
{
    return m_title;
}

bool AudioController::isPlaying() const
{
    return m_player->playbackState() == QMediaPlayer::PlayingState;
}

void AudioController::setSongIndex(int index)
{
    m_previousIndex.push_back(index);
    m_pos = 0;
    updateContent();
    emit songIndexChanged();
}
void AudioController::updateContent()
{
    auto info = m_model->songInfoAt(songIndex());
    if (info == nullptr)
        return;
    m_title = QString("%1 - %2").arg(info->m_title, info->m_artist);
    setContent(QUrl::fromLocalFile(info->m_filepath));
    m_player->setSource(m_content);

    emit titleChanged();
}
void AudioController::setMode(PlayingMode mode)
{
    if (mode == m_mode)
        return;
    m_mode = mode;
    emit modeChanged();
}
void AudioController::setVolume(float vol)
{
    qDebug() << "vol" << vol;
    m_audioOutput->setVolume(vol);
}
void AudioController::setSeek(qint64 move)
{
    m_player->setPosition(move);
}

void AudioController::setContent(const QUrl& url)
{
    if (url == m_content)
        return;
    m_content = url;
    emit contentChanged();
}

void AudioController::play()
{
    if (!m_content.isValid())
        updateContent();
    m_player->play();
}

QObject* AudioController::videoOutput() const
{
    return m_player->videoOutput();
}

void AudioController::setVideoOutput(QObject* output)
{
    m_player->setVideoOutput(output);
}

void AudioController::setMuted(bool b)
{
    m_audioOutput->setMuted(b);
}

TagFilteredModel *AudioController::filteredTagModel() const
{
    return m_filterTagModel.get();
}

TagModel* AudioController::tags() const
{
    return m_tagsModel.get();
}
