#include "maincontroller.h"
#include "constants.h"
#include <QJsonArray>
#include <QJsonObject>

MainController::MainController(QObject* parent)
    : QObject { parent }
    , m_clientCtrl(new ClientController)
    , m_audioCtrl(new AudioController)
{
    m_clientCtrl->setUrl(QUrl("ws://localhost:10999"));

    connect(m_clientCtrl.get(), &ClientController::songDataChanged, m_audioCtrl.get(), &AudioController::setContentData);
    connect(m_clientCtrl.get(), &ClientController::songFileChanged, m_audioCtrl.get(), &AudioController::setContent);
    connect(m_clientCtrl.get(), &ClientController::seekChanged, this, &MainController::setPosition);
    connect(m_clientCtrl.get(), &ClientController::songInfoChanged, this, [this](const QJsonObject& obj) {
        m_artist = obj[constants::info::artist].toString();
        m_title = obj[constants::info::title].toString();
        m_index = obj[constants::info::index].toInt();
        m_duration = obj[constants::info::time].toInteger() * 1000;
        emit currentSongChanged();
    });

    connect(m_clientCtrl.get(), &ClientController::modelDataChanged, this, [this](const QJsonObject& obj) {
        auto model = m_audioCtrl->model();
        auto songArray = obj[constants::json::songs].toArray();
        QList<QVariantMap> pathlist;

        for (auto const& songref : songArray) {
            auto song = songref.toObject();
            pathlist.append({ { "path", song[constants::info::path].toString() },
                { "artist", song[constants::info::artist].toString() },
                { "album", song[constants::info::album].toString() },
                { "title", song[constants::info::title].toString() },
                { "time", song[constants::info::time].toInt() } });
        }
        model->appendSongs(pathlist);
    });

    m_clientCtrl->connectTo();
}

AudioController* MainController::audioCtrl() const
{
    return m_audioCtrl.get();
}

ClientController* MainController::clientCtrl() const
{
    return m_clientCtrl.get();
}

void MainController::play(int index)
{
    QHash<QString, QVariant> params;
    if (index >= 0)
        params.insert(constants::info::index, index);

    m_clientCtrl->sendCommand(constants::play, params);
}

void MainController::previous()
{
    m_clientCtrl->sendCommand(constants::previous);
}

void MainController::next()
{
    m_clientCtrl->sendCommand(constants::next);
}

void MainController::stop()
{
    m_clientCtrl->sendCommand(constants::stop);
}

void MainController::pause()
{
    m_clientCtrl->sendCommand(constants::pause);
}

void MainController::setPlayingMode(PlayingMode mode)
{
    switch (mode) {
    case PlayingMode::Forward:
        m_clientCtrl->sendCommand(constants::forward);
        break;
    case PlayingMode::Loop:
        m_clientCtrl->sendCommand(constants::loop);
        break;
    case PlayingMode::Shuffle:
        m_clientCtrl->sendCommand(constants::random);
        break;
    case PlayingMode::Unique:
        m_clientCtrl->sendCommand(constants::unique);
        break;
    }
    m_mode = mode;
}

MainController::PlayingMode MainController::mode() const
{
    return m_mode;
}

bool MainController::syncWithServer() const
{
    return m_syncWithServer;
}

void MainController::setSyncWithServer(bool newSyncWithServer)
{
    if (m_syncWithServer == newSyncWithServer)
        return;
    m_syncWithServer = newSyncWithServer;
    emit syncWithServerChanged();

    m_clientCtrl->sendCommand(m_syncWithServer ? constants::mute : constants::volumeOn);
    m_clientCtrl->sendCommand(m_syncWithServer ? constants::streamMusic : constants::playOnServer);
}

qreal MainController::position() const
{
    if (m_syncWithServer)
        return m_audioCtrl->seek();
    return m_position;
}

void MainController::setPosition(qreal newPosition)
{
    // qDebug() << "position" << newPosition << m_syncWithServer << m_duration;
    if (qFuzzyCompare(m_position, newPosition))
        return;

    if (m_syncWithServer)
        m_audioCtrl->setSeek(newPosition);
    m_position = newPosition;
    emit positionChanged();
}

QString MainController::artist() const
{
    return m_artist;
}

QString MainController::title() const
{
    return m_title;
}

qint64 MainController::duration() const
{
    return m_duration;
}

qint64 MainController::index() const
{
    return m_index;
}

QImage MainController::image() const
{
    return m_image;
}

bool MainController::hasImage() const
{
    return !m_img.isNull();
}
