#ifndef SERVERTEXT_H
#define SERVERTEXT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "sendfileadaptor.h"

class SendingServer : public QObject
{
    Q_OBJECT
public:
    explicit SendingServer(QObject *parent = 0);
    //void processCommand(QStringList list);
    void startListing();


public slots:
    void sendFile(QString uri);

private slots:
    void sessionOpened();
    void readCommand();
    
private:
    QTcpServer * m_tcpServer;
    QTcpSocket* m_client;
    quint16 m_blockSize;
    SendFileAdaptor* m_adaptor;


};

#endif // SERVERTEXT_H
