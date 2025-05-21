#include "ClientController.h"
#include "constants.h"
#include "messagefactory.h"
#include <QAudioOutput>
#include <QJsonArray>
#include <QJsonObject>

ClientController::ClientController(QObject* parent)
    : QObject { parent }
    , m_socket(new QWebSocket)
{

    connect(m_socket, &QWebSocket::binaryMessageReceived, this, &ClientController::receivedBinaryData);
    connect(m_socket, &QWebSocket::textMessageReceived, this, &ClientController::receivedTextData);
    connect(m_socket, &QWebSocket::connected, this, [this]() {
        if (!m_connected) {
            m_connected = true;
            emit connectedChanged();
        }
    });
    connect(m_socket, &QWebSocket::disconnected, this, [this]() {
        if (m_connected) {
            m_connected = false;
            emit connectedChanged();
            connectTo();
        }
    });
    connect(m_socket, &QWebSocket::errorOccurred, this, [this]() {
        qDebug() << "error socket:" << m_socket->errorString();
    });
}

void ClientController::connectTo()
{
    m_socket->open(m_url);
}

void ClientController::receivedBinaryData(const QByteArray& array)
{
    qDebug() << "data received" << array.size();
    QByteArray song;
    song.append(static_cast<quint8>(constants::DataType::MusicFile));

    QByteArray img;
    img.append(static_cast<quint8>(constants::DataType::ImageFile));

    if(array.startsWith(song))
        emit songDataChanged(array.sliced(song.size()));
    else if(array.startsWith(img))
        emit imageChanged(array.sliced(img.size()));
}

void ClientController::receivedTextData(const QString& message)
{

    auto msg = factory::messageToObject(message);
    auto act = factory::actionToEnum(msg);

    auto obj = msg[constants::audio].toObject();

    // qDebug() << "text received" << act << constants::NewSongAct;
    switch (act) {
    case constants::AudioModel:
        emit modelDataChanged(obj);
        break;
    case constants::NewSongAct:
        qDebug() << obj[constants::uri].toString();
        emit songFileChanged(QUrl(obj[constants::uri].toString()));
        break;
    case constants::SelectAct:
        emit songInfoChanged(obj);
        break;
    case constants::SeekAct:
        emit seekChanged(obj[constants::info::value].toDouble());
        break;
    case constants::StateAct:
        emit stateChange(obj[constants::state].toInt());
        break;
    default:
        break;
    }
}

QUrl ClientController::url() const
{
    return m_url;
}

void ClientController::setUrl(const QUrl& newUrl)
{
    if (m_url == newUrl)
        return;
    m_url = newUrl;
    emit urlChanged();
}

void ClientController::sendCommand(const QString& cmd, const QHash<QString, QVariant>& params)
{
    m_socket->sendTextMessage(factory::buildMessage(constants::audio, cmd, params));
}

bool ClientController::connected() const
{
    return m_connected;
}
