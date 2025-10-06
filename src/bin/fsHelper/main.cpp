#include <QApplication>

#include "mainwindow.h"

int main(int arg, char** argc)
{
    QApplication app(arg, argc);
    MainWindow window;

    window.show();

    return app.exec();
}
