#ifndef SERVERTEXT_H
#define SERVERTEXT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "adaptor.h"

class ServerText : public QObject
{
    Q_OBJECT
public:
    explicit ServerText(QObject *parent = 0);
    void processCommand(QStringList list);
    void startListing();
    
private slots:
    void sessionOpened();
    void readCommand();
    
private:
    DbusAdaptor* m_adap ;
    QTcpServer * m_tcpServer;
    QTcpSocket* m_client;
    quint16 m_blockSize;


};

#endif // SERVERTEXT_H
