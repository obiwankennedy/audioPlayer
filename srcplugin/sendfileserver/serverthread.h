#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include "sendingserver.h"

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(QObject *parent = 0);
    void run();


    
private:
    SendingServer* m_server;
    
};

#endif // SERVERTHREAD_H
