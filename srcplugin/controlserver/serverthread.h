#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include "servertext.h"

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(QObject *parent = 0);
    void run();


    
private:
    ServerText* text;
    
};

#endif // SERVERTHREAD_H
