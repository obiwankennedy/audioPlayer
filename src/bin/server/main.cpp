#include <QCoreApplication>

#include "servermanager.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("AudioServer"));
    app.setOrganizationDomain(QStringLiteral("org.rolisteam"));


    ServerManager server;
    server.startListening();


    return app.exec();
}
