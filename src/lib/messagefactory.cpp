#include "messagefactory.h"

#include <QJsonDocument>
#include <QJsonObject>
#include "constants.h"

namespace factory
{

QJsonObject hashToJSon(const QHash<QString, QVariant>& parameter)
{
    QJsonObject obj;
    using namespace constants;

    for(auto [key,val] : parameter.asKeyValueRange())
    {
        obj[key] = val.toJsonValue();
    }
    return obj;
}

QByteArray buildMessage(const QString &service, const QString &action, const QHash<QString, QVariant>& parameter)
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

QHash<QString, QVariant> model2Parameter(AudioFileModel *model)
{
    QHash<QString, QVariant> res;

    auto songs = model->songs();
    QList<QHash<QString, QVariant>> list;
    int i = 0;
    for(auto s : songs)
    {
        QHash<QString, QVariant> info;
        info[constants::info::album] = s->m_album;
        info[constants::info::time] = s->m_album;
        info[constants::info::title] = s->m_album;
        info[constants::info::artiste] = s->m_album;
        info[constants::info::index] = i;
        ++i;
        list.append(info);
    }
    res.insert(constants::json::songs, QVariant::fromValue(list));
    return res;
}

constants::Action actionToEnum(const QJsonObject &obj)
{
    static QHash<QString, constants::Action> actions{
        {constants::play,constants::PlayAct},
        {constants::stop,constants::StopAct},
        {constants::previous,constants::PreviousAct},
        {constants::select,constants::SelectAct},
        {constants::loop,constants::LoopAct},
        {constants::random,constants::RandomAct},
        {constants::format,constants::AudioFormat},
        {constants::model,constants::AudioModel},
        {constants::next,constants::NextAct}};

    return actions.value(obj[constants::json::action].toString());
}

QJsonObject messageToObject(const QString &message)
{
    return QJsonDocument::fromJson(message.toLocal8Bit()).object();
}

}
