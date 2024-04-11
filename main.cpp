/***************************************************************************
 *   Copyright (C) 2007 by Renaud Guezennec   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "uiwatchdog.h"
#include <QAbstractItemModel>
#include <QApplication>
#include <QOpenGLContext>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QSurfaceFormat>

#include "audiocontroller.h"
#include "audiofilemodel.h"
//#include "commandserver.h"
#include "filteredmodel.h"
#include "maincontroller.h"
#include "worker/theme.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("AudioPlayer"));
    app.setOrganizationDomain(QStringLiteral("org.rolisteam"));
    auto format= QSurfaceFormat::defaultFormat();
    if(QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL)
    {
        format.setVersion(3, 2);
        format.setProfile(QSurfaceFormat::CoreProfile);
    }
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    QQuickStyle::setStyle("Universal");

    std::unique_ptr<MainController> mainController(new MainController);
    QQmlApplicationEngine qmlEngine;

    qmlEngine.addImageProvider("album", mainController->audioCtrl()->pictureProvider());

    qmlRegisterSingletonInstance("AudioPlayer", 1, 0, "MainController", mainController.get());
    qmlRegisterSingletonInstance("Customization", 1, 0, "Theme", new Theme(&qmlEngine));

    // qmlRegisterType<MainController>("AudioPlayer", 1, 0, "MainController");
    qmlRegisterUncreatableType<AudioController>("AudioPlayer", 1, 0, "AudioController", "Just for enum");
    qRegisterMetaType<QAbstractItemModel*>();
    qRegisterMetaType<FilteredModel*>();
    qRegisterMetaType<AudioFileModel*>();
    qRegisterMetaType<AudioController*>();
    qRegisterMetaType<AudioController::PlayingMode>();

    qmlEngine.load(QLatin1String("qrc:/resources/qml/main.qml"));

    return app.exec();
}
