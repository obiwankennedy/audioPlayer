#include "messagefactory.h"

#include "constants.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QBuffer>

namespace factory {

QJsonObject hashToJSon(const QHash<QString, QVariant>& parameter)
{
    QJsonObject obj;
    using namespace constants;

    for (auto [key, val] : parameter.asKeyValueRange()) {
        obj[key] = val.toJsonValue();
    }
    return obj;
}

QByteArray buildMessage(const QString& service, const QString& action, const QHash<QString, QVariant>& parameter)
{
    QJsonObject obj;
    using namespace constants;
    obj[json::service] = service;
    obj[json::action] = action;
    obj[json::parameter] = hashToJSon(parameter);

    QJsonDocument doc;

    doc.setObject(obj);

    return doc.toJson();
}

QJsonArray model2Parameter(AudioFileModel* model)
{
    QJsonArray res;
    auto const& songs = model->songs();
    int i = 0;
    for (auto s : songs) {
        QJsonObject info;
        info[constants::info::album] = s->m_album;
        info[constants::info::time] = static_cast<int>(s->m_time);
        info[constants::info::title] = s->m_title;
        info[constants::info::artist] = s->m_artist;
        info[constants::info::path] = s->m_filepath;
        info[constants::info::tags] = QJsonArray::fromStringList(s->m_tags);
        info[constants::info::index] = i;
        ++i;
        res.append(info);
    }
    return res;
}

QByteArray imageToArray(const QImage& img)
{
    QByteArray ba;
    {
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        img.save(&buffer, "PNG");
    }
    return ba;
}

constants::Action actionToEnum(const QJsonObject& obj)
{
    static QHash<QString, constants::Action> actions {
        { constants::play, constants::PlayAct },
        { constants::stop, constants::StopAct },
        { constants::previous, constants::PreviousAct },
        { constants::select, constants::SelectAct },
        { constants::loop, constants::LoopAct },
        { constants::random, constants::RandomAct },
        { constants::volume, constants::SetVolumeAct },
        { constants::model, constants::AudioModel },
        { constants::newSong, constants::NewSongAct },
        { constants::volumeOn, constants::VolumeOnAct },
        { constants::seek, constants::SeekAct },
        { constants::mute, constants::MuteAct },
        { constants::state, constants::StateAct },
        { constants::streamMusic, constants::StreamMusicAct },
        { constants::playOnServer, constants::PlayOnServerAct },
        { constants::setTag, constants::SetTagAct },
        { constants::RemoveTag, constants::RemoveTagAct },
        { constants::next, constants::NextAct }
    };

    return actions.value(obj[constants::json::action].toString());
}

QJsonObject messageToObject(const QString& message)
{
    return QJsonDocument::fromJson(message.toLocal8Bit()).object();
}

QByteArray fileToArray(const QString& filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "error - Can't read:" << filename;
    }

    return file.readAll();
}
}
