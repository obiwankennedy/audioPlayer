/***************************************************************************
 *	Copyright (C) 2020 by Renaud Guezennec                               *
 *   http://www.rolisteam.org/contact                                      *
 *                                                                         *
 *   This software is free software; you can redistribute it and/or modify *
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
#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "audiocontroller.h"

class CommandServer : public QObject
{
    Q_OBJECT
public:
    explicit CommandServer(QObject* parent= nullptr);

    void startListing();

public slots:
    void sendOffStatus(const QString& status);

signals:
    void next();
    void pause();
    void play();
    void previous();
    void increase();
    void decrease();
    void changeMode(AudioController::PlayingMode mode);
    void volume(int v);

private slots:
    void sessionOpened();
    void readCommand();
    void processCommand(QStringList list);

private:
    QTcpServer* m_server= nullptr;
    QTcpSocket* m_client= nullptr;
};

#endif // COMMANDSERVER_H
