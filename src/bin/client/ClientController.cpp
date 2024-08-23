#include "ClientController.h"
#include "messagefactory.h"
#include "constants.h"
#include <QJsonObject>

ClientController::ClientController(QObject *parent)
    : QObject{parent}, m_socket(new QWebSocket), m_buffer(&m_data)
{
    connect(m_socket, &QWebSocket::binaryMessageReceived, this, &ClientController::receivedBinaryData);
    connect(m_socket, &QWebSocket::textMessageReceived, this, &ClientController::receivedTextData);
    connect(m_socket, &QWebSocket::errorOccurred, this, [this](){
        qDebug() << m_socket->errorString();
    });

    m_buffer.open(QIODevice::ReadWrite);

    m_sink = new QAudioSink();
    connect(m_sink, &QAudioSink::stateChanged, this, [this](QtAudio::State state){
        qDebug() << "client state:" << state;
        m_state = state;

        if(state == QAudio::StoppedState)
        {
            if(m_sink->error() != QAudio::NoError)
            {
                qDebug() << "client Error:" << m_sink->error();
            }
        }
    });
}

void ClientController::connectTo()
{
    m_socket->open(m_url);
}

void ClientController::receivedBinaryData(const QByteArray& array)
{
    if(!m_sink)
        return;

    m_data.append(array);
    /*auto pos = m_buffer.pos();
    m_buffer.write(array);
    m_buffer.seek(pos);*/

    qDebug() << "client data" << m_data.size() << m_state << m_buffer.pos();

    if(m_state != QtAudio::ActiveState)
    {
        qDebug() << "Start reading" << m_buffer.size();
        m_sink->start(&m_buffer);
    }
}

void ClientController::receivedTextData(const QString& message)
{

    auto msg = factory::messageToObject(message);
    auto act = factory::actionToEnum(msg);

    qDebug() << "text received" << act << msg;
    switch(act)
    {
    case constants::AudioModel:
        qDebug() << "model:" <<msg;
        break;
    case constants::AudioFormat:
    {
        /*QAudioFormat format;
        format.setSampleFormat(static_cast<QAudioFormat::SampleFormat>(msg[constants::sampleFormat].toInt()));
        format.setChannelCount(msg[constants::channelCount].toInt());
        format.setSampleRate(msg[constants::sampleRate].toInt());*/
        qDebug() << "client CReate m_sink";

    }
        break;
    default:
        break;
    }
}

QUrl ClientController::url() const
{
    return m_url;
}

void ClientController::setUrl(const QUrl &newUrl)
{
    if (m_url == newUrl)
        return;
    m_url = newUrl;
    emit urlChanged();
}

void ClientController::play()
{
    m_socket->sendTextMessage(factory::buildMessage(constants::audio,constants::play,{}));
}
void ClientController::previous()
{
    m_socket->sendTextMessage(factory::buildMessage(constants::audio,constants::previous,{}));
}
void ClientController::next()
{
    m_socket->sendTextMessage(factory::buildMessage(constants::audio,constants::next,{}));
}
