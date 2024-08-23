#include "servermanager.h"
#include "messagefactory.h"
#include "constants.h"
#include <QJsonObject>

ServerManager::ServerManager(QObject *parent)
    : QObject{parent}, m_server(new QWebSocketServer("MusicServer",QWebSocketServer::NonSecureMode,this)), m_ctrl(new MainController(nullptr)),
    m_decoder(new WebSocketDecoder)
{
    auto audio = m_ctrl->audioCtrl();

    audio->setDecoder(m_decoder.get());


    connect(m_decoder.get(), &QAudioDecoder::formatChanged, this, [this](const QAudioFormat& format){
        auto msg = factory::buildMessage(constants::audio,constants::format,{{constants::sampleRate, format.sampleRate()},
                                                                               {constants::channelCount, format.channelCount()},
                                                                               {constants::sampleFormat, format.sampleFormat()}});
        qDebug() << "server formatChanged";
        std::for_each(std::begin(m_clients), std::end(m_clients), [msg](QWebSocket* client){
            client->sendTextMessage(msg);
        });
    });


    connect(m_decoder.get(), &QAudioDecoder::bufferReady, this, [this](){
        auto buffer = m_decoder->read();
        QByteArray data(buffer.data<char>(), buffer.byteCount());
        qDebug() << "server bufferReady";
        std::for_each(std::begin(m_clients), std::end(m_clients), [data](QWebSocket* client){
            client->sendBinaryMessage(data);
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
    qDebug() << "server processText";
    auto s = qobject_cast<QWebSocket*>(sender());
    if(!s)
        return;

    auto msg = factory::messageToObject(message);
    auto act = factory::actionToEnum(msg);
    auto audio = m_ctrl->audioCtrl();

    switch(act)
    {
    case constants::Action::PlayAct:
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
    case constants::Action::SelectAct:
        audio->filteredModel()->setSearch(msg[constants::json::pattern].toString());
        break;
    case constants::Action::AudioFormat:
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

    s->sendTextMessage(factory::buildMessage(constants::audio,constants::model,b));

    auto format = m_decoder->audioFormat();
    auto msg = factory::buildMessage(constants::audio,constants::format,{{constants::sampleRate, format.sampleRate()},
                                                                           {constants::channelCount, format.channelCount()},
                                                                           {constants::sampleFormat, format.sampleFormat()}});

    s->sendTextMessage(msg);
}
