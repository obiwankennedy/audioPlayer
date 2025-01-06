#include "servermanager.h"
#include "messagefactory.h"
#include "constants.h"
#include <QJsonObject>
#include <QtConcurrent>

ServerManager::ServerManager(QObject *parent)
    : QObject{parent}, m_server(new QWebSocketServer("MusicServer",QWebSocketServer::NonSecureMode,this)), m_ctrl(new MainController(nullptr))
{
    auto audio = m_ctrl->audioCtrl();

    connect(audio, &AudioController::contentChanged, this, [this](){
        if(!m_streamMusic)
            return;
        const QUrl content = m_ctrl->audioCtrl()->content();
            auto msg = factory::buildMessage(constants::audio,constants::newSong,{{constants::uri,content.toString()}});
            std::for_each(std::begin(m_clients), std::end(m_clients), [msg](QWebSocket* client){
                client->sendTextMessage(msg);
            });
            auto data = factory::fileToArray(content.toLocalFile());
            std::for_each(std::begin(m_clients), std::end(m_clients), [data](QWebSocket* client){
                client->sendBinaryMessage(data);
            });
    });

    connect(audio, &AudioController::titleChanged, this, [this](){
        auto audio = m_ctrl->audioCtrl();
        auto info = audio->model()->songInfoAt(audio->songIndex());

        auto msg = factory::buildMessage(constants::audio,constants::select,{{constants::info::album,audio->albumArt()},
            {constants::info::album,info->m_album},
            {constants::info::index,audio->songIndex()},
            {constants::info::title,info->m_title},
            {constants::info::artist,info->m_artist},
            {constants::info::time,info->m_time}
        });
        std::for_each(std::begin(m_clients), std::end(m_clients), [msg](QWebSocket* client){
            client->sendTextMessage(msg);
        });
    });

    connect(audio, &AudioController::seekChanged, this, [this](){
        auto audio = m_ctrl->audioCtrl();
        auto msg = factory::buildMessage(constants::audio,constants::seek,{{constants::info::value, audio->seek()}});
        std::for_each(std::begin(m_clients), std::end(m_clients), [msg](QWebSocket* client){
            client->sendTextMessage(msg);
        });
    });

    connect(m_server.get(), &QWebSocketServer::newConnection, this, [this](){
        auto c = m_server->nextPendingConnection();
        qDebug() << "New connection";
        connect(c, &QWebSocket::binaryMessageReceived, this, &ServerManager::processBinary);
        connect(c, &QWebSocket::textMessageReceived, this, &ServerManager::processText);
        m_clients.push_back(c);
        updateClient(c);
    } );
}

void ServerManager::startListening()
{
    if(m_server->listen(QHostAddress::Any, m_port))
        qDebug() << "Server is listening";
}

int ServerManager::port() const
{
    return m_port;
}

void ServerManager::setPort(int newPort)
{
    if (m_port == newPort)
        return;
    m_port = newPort;
    emit portChanged();
}

void ServerManager::processText(const QString& message)
{
    auto s = qobject_cast<QWebSocket*>(sender());
    if(!s)
        return;

    auto msg = factory::messageToObject(message);
    auto act = factory::actionToEnum(msg);
    auto audio = m_ctrl->audioCtrl();
    qDebug() << "server processText" << message;

    switch(act)
    {
    case constants::Action::PlayAct:
        if(msg.contains(constants::info::index))
        {
            auto index = msg[constants::info::index].toInt();
            audio->setSongIndex(index);
        }
        audio->play();
        break;
    case constants::Action::StopAct:
        audio->pause();
        break;
    case constants::Action::NextAct:
        audio->next();
        break;
    case constants::Action::PreviousAct:
        audio->previous();
        break;
    case constants::Action::LoopAct:
        audio->setMode(AudioController::LOOP);
        break;
    case constants::Action::RandomAct:
        audio->setMode(AudioController::SHUFFLE);
        break;
    case constants::Action::VolumeOnAct:
        audio->setMuted(false);
        break;
    case constants::Action::MuteAct:
        audio->setMuted(true);
        break;
    case constants::Action::SelectAct:
        audio->filteredModel()->setSearch(msg[constants::json::pattern].toString());
        break;
    case constants::Action::StreamMusicAct:
        m_streamMusic = true;
        break;
    case constants::Action::PlayOnServerAct:
        m_streamMusic = false;
        break;
    default:
        break;
    }


}
void ServerManager::processBinary()
{
    qDebug() << "server processBinary";
}

void ServerManager::updateClient(QWebSocket* s)
{
    if(!s)
        return;

    auto b = factory::model2Parameter(m_ctrl->audioModel());
    auto msg = factory::buildMessage(constants::audio,constants::model,{{constants::json::songs, b}});
    s->sendTextMessage(msg);
}
