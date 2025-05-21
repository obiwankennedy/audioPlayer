#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QByteArray>
#include <QJsonObject>
#include <QObject>
#include <QQmlEngine>
#include <QUrl>
#include <QWebSocket>

class ClientController : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged FINAL)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged FINAL)
public:
    explicit ClientController(QObject* parent = nullptr);

    QUrl url() const;
    void setUrl(const QUrl& newUrl);

    bool connected() const;

public slots:
    void connectTo();

    void receivedBinaryData(const QByteArray& array);
    void receivedTextData(const QString& message);

    void sendCommand(const QString& cmd, const QHash<QString, QVariant>& params = {});

signals:
    void urlChanged();
    void connectedChanged();
    void modelDataChanged(const QJsonObject& obj);
    void songDataChanged(const QByteArray& array);
    void imageChanged(const QByteArray& data);
    void songFileChanged(const QUrl& title);
    void seekChanged(qreal p);
    void songInfoChanged(const QJsonObject& obj);
    void stateChange(int state);

private:
    QWebSocket* m_socket;
    QUrl m_url;
    bool m_connected { false };
};

#endif // CLIENTCONTROLLER_H
