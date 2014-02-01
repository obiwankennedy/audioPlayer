#include "servertext.h"
#include <QDebug>

#define PORT 40000


ServerText::ServerText(QObject *parent) :
    QObject(parent),m_blockSize(0)
{
    m_adap = new DbusAdaptor("eu.renaudguezennec","/",QDBusConnection::sessionBus(),0);
    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer,SIGNAL(newConnection()),this,SLOT(sessionOpened()));

}

void ServerText::startListing()
{
    if (!m_tcpServer->listen(QHostAddress::Any,PORT))
    {
        //qDebug() << "Error! no listen on the server";
    }
}
void ServerText::sessionOpened()
{
  m_client = m_tcpServer->nextPendingConnection();
  connect(m_client,SIGNAL(readyRead()),this,SLOT(readCommand()));
}

void ServerText::processCommand(QStringList list)
{
  //  qDebug() << "Process command" << list;
    if(list.empty())
    {
        //displayHelp();
        //exit(-1);
    }

    if((list.at(0)=="-n")||(list.at(0)=="next"))
    {
        m_adap->nextSong();
    }
    else if((list.at(0)=="-p")||(list.at(0)=="previous"))
    {
        m_adap->previousSong();
    }
    else if((list.at(0)=="-i")||(list.at(0)=="increase"))
    {
        m_adap->increaseSong();
    }
    else if((list.at(0)=="-d")||(list.at(0)=="decrease"))
    {
        m_adap->decreaseSong();
    }
    else if((list.at(0)=="-v"))
    {
        if(list.size()>=2)
        {
            int i = list.at(1).toInt();
           m_adap->setVolume(i);
        }
    }
    else if((list.at(0)=="play"))
    {
        m_adap->playSong();
    }
    else if((list.at(0)=="pause"))
    {
        m_adap->pauseSong();
    }

}

void ServerText::readCommand()
{
        quint16 blockSize=0;
        QDataStream in(m_client);
        in.setVersion(QDataStream::Qt_4_0);

        if (blockSize == 0) {
            if (m_client->bytesAvailable() < (int)sizeof(quint16))
                return;

            in >> blockSize;
        }

        if (m_client->bytesAvailable() < blockSize)
            return;

        QString nextCommand;
        in >> nextCommand;

        QStringList arg=nextCommand.split(" ",QString::SkipEmptyParts);
        processCommand(arg);

}
