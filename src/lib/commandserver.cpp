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
#include "commandserver.h"

CommandServer::CommandServer(QObject* parent) : QObject(parent)
{
    m_server= new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &CommandServer::sessionOpened);
}

void CommandServer::startListing()
{
    auto ok= m_server->listen(QHostAddress::Any, 4000);

    qDebug() << "listening" << ok;
}

void CommandServer::sendOffStatus(const QString& status)
{
    if(nullptr == m_client)
        return;

    m_client->write(status.toUtf8());
}

void CommandServer::sessionOpened()
{
    qDebug() << "session openned";
    m_client= m_server->nextPendingConnection();
    connect(m_client, &QTcpSocket::readyRead, this, &CommandServer::readCommand);
}

void CommandServer::processCommand(QStringList list)
{
    if(list.empty())
        return;

    if((list.at(0) == "-n") || (list.at(0) == "next"))
    {
        emit next();
    }
    else if((list.at(0) == "-p") || (list.at(0) == "previous"))
    {
        emit previous();
    }
    else if((list.at(0) == "-i") || (list.at(0) == "increase"))
    {
        increase();
    }
    else if((list.at(0) == "-d") || (list.at(0) == "decrease"))
    {
        decrease();
    }
    else if((list.at(0) == "-v"))
    {
        if(list.size() >= 2)
        {
            int i= list.at(1).toInt();
            emit volume(i);
        }
    }
    else if((list.at(0) == "play"))
    {
        emit play();
    }
    else if((list.at(0) == "pause"))
    {
        emit pause();
    }
}

void CommandServer::readCommand()
{
    auto byte= m_client->read(100);

    if(byte.isEmpty())
        return;

    QString nextCommand(byte);

    QStringList arg= nextCommand.split(" ", Qt::SkipEmptyParts);
    processCommand(arg);
}
