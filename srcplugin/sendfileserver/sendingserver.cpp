#include "sendingserver.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#define PORT 40001


SendingServer::SendingServer(QObject *parent) :
    QObject(parent),m_blockSize(0),m_client(NULL)
{
    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer,SIGNAL(newConnection()),this,SLOT(sessionOpened()));
    m_adaptor = new SendFileAdaptor("eu.playview.renaudguezennec","/",QDBusConnection::sessionBus(),0);

    connect(m_adaptor,SIGNAL(sendFileToPhone(QString)),this,SLOT(sendFile(QString)));

}

void SendingServer::startListing()
{
    if (!m_tcpServer->listen(QHostAddress::Any,PORT))
    {
        //qDebug() << "Error! no listen on the server";
        /*
         *
         * Quiche en entrée salée
         * purée de carottes au cumin
         * et
         * mange-tout ou celeri
         * et
         * champignon
         *
         *
         *
         * */
    }
}
void SendingServer::sessionOpened()
{
    m_client = m_tcpServer->nextPendingConnection();
    connect(m_client,SIGNAL(readyRead()),this,SLOT(readCommand()));
}

void SendingServer::readCommand()
{
    qDebug() << "connection received";
}
void SendingServer::sendFile(QString uri)
{
    if(NULL==m_client)
        return;
    QFile inputFile(uri);
    QFileInfo info(uri);

    int sizeBuf = sizeof(quint32)+sizeof(QChar)*info.fileName().size();

  char* fileNameData= new char[sizeBuf];
  char* position=fileNameData;
  *((quint32 *)position)=info.fileName().size();

  position+= sizeof(quint32);

  memcpy(position,info.fileName().toLatin1().data(),sizeof(QChar)*info.fileName().size());




  m_client->write(fileNameData,sizeBuf);








    QByteArray read;
    if(m_client->isWritable())
    {

        inputFile.open(QIODevice::ReadOnly);
        while(1)
        {
            read.clear();
            read = inputFile.read(32768*8);
            qDebug() << "Read : " << read.size();
            if(read.size()==0)
                break;

            qDebug() << "Written : " << m_client->write(read);
            m_client->waitForBytesWritten();
            read.clear();
        }
        inputFile.close();
    }
}
