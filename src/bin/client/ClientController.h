#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QQmlEngine>
#include <QWebSocket>
#include <QAudioSink>
#include <QAudioFormat>
#include <QBuffer>
#include <QByteArray>

class ClientController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged FINAL)

public:
    explicit ClientController(QObject *parent = nullptr);

    QUrl url() const;
    void setUrl(const QUrl &newUrl);

public slots:
    void connectTo();

    void receivedBinaryData(const QByteArray &array);
    void receivedTextData(const QString &message);

    void play();
    void previous();
    void next();

signals:

    void urlChanged();

private:
    QWebSocket* m_socket;
    QAudioSink* m_sink{nullptr};
    QAudioFormat format;
    QBuffer m_buffer;
    QByteArray m_data;
    QUrl m_url;
    QtAudio::State m_state{QAudio::StoppedState};
};

#endif // CLIENTCONTROLLER_H
