#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QWebSocket>
#include <QWebSocketServer>
#include <memory.h>
#include "appcontroller.h"
#include "websocketdecoder.h"

class ServerManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged FINAL)
public:
    explicit ServerManager(QObject *parent = nullptr);


    int port() const;
    void setPort(int newPort);

    void processText(const QString& message);
    void processBinary();


public slots:
    void startListening();
    void updateClient(QWebSocket* s);

signals:

    void portChanged();

private:
    std::unique_ptr<QWebSocketServer> m_server;
    std::vector<QWebSocket*> m_clients;
    std::unique_ptr<AppController> m_ctrl;
    bool m_streamMusic{false};
    int m_port{10999};
};

#endif // SERVERMANAGER_H
