#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int arg, char** argv)
{
    QGuiApplication app(arg, argv);


    app.setOrganizationName(QStringLiteral("AudioClient"));
    app.setOrganizationDomain(QStringLiteral("org.rolisteam"));

    QQuickStyle::setStyle("Universal");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [](QObject *obj, const QUrl &objUrl) {
            qDebug() << "Object Created:" << objUrl;
            if (!obj)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.loadFromModule("Views", "Main");


    return app.exec();
}
