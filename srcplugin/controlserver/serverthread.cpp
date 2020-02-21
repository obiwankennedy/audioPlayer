#include "serverthread.h"

ServerThread::ServerThread(QObject* parent) : QThread(parent) {}
void ServerThread::run()
{
    text= new ServerText();
    text->startListing();

    exec();
}
