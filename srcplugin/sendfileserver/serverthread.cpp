#include "serverthread.h"

ServerThread::ServerThread(QObject *parent) :
    QThread(parent)
{

}
void ServerThread::run()
{
    m_server = new SendingServer();
    m_server->startListing();

    exec();
}
