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

#include "playlistgenerator.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
/**
        \author Renaud Guezennec <renaud.guezennec@gmail.com>
 * \fn main
 * \brief Main function , load translation file , start the user interface and the event loop.
 * \version 1.0
 * \date 21/04/2008
 * \bug no known
 * \warning no known
 * \todo   no
 */
int main(int argc, char* argv[])
{
    // srand(clock());
    // Q_INIT_RESOURCE(playlistgenerator);
    QApplication app(argc, argv);
    app.setApplicationName(QCoreApplication::tr("PlayListGenerator"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QStringList args= app.arguments();
    QTranslator translator;
    QTranslator translator2;
    translator.load("translations/audioPlayer_" + QLocale::system().name(), qApp->applicationDirPath());

    translator2.load(":/resources/translations/qt_" + QLocale::system().name(), qApp->applicationDirPath());
    app.installTranslator(&translator);
    app.installTranslator(&translator2);
    PlayListGenerator mw;

    if(args.count() > 1)
    {
        mw.loadFile(QString(args[1]));
    }
    mw.show();
    // mw.refreshPlugin();
    return app.exec();
}
