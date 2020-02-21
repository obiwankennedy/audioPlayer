/***************************************************************************
 *   Copyright (C) 2009 by Renaud Guezennec   *
 *   renaud.guezennec@gmail.com   *
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
#include "songpluginmanager.h"

#include <QtGui>

#include "songplugin.h"
#include "songpluginmanager.h"

#include "songlistplugin.h"

SongPluginManager::SongPluginManager(QMainWindow* mainwindow) : m_mainwindow(mainwindow)
{
    QDir pluginsDir= QDir(qApp->applicationDirPath());

    pluginsDir.cd("plugins");

    foreach(QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

        QObject* plugin= loader.instance();

        if(plugin)
        {
            SongInterface* op= qobject_cast<SongInterface*>(plugin);
            if(op)
            {
                m_actionList << op;

                op->getName();
            }
        }
    }
}
void SongPluginManager::displayPreviousState()
{
    foreach(SongInterface* op, m_actionList)
    {
        if(op->isVisible())
        {
            m_mainwindow->addDockWidget(op->orientation(), op->getWidget());
        }
    }
}

SongPluginManager* SongPluginManager::m_instance= 0;

SongPluginManager::~SongPluginManager() {}
void SongPluginManager::playingSongChanged(SongFields* a)
{
    foreach(SongInterface* op, m_actionList)
    {
        op->SetSong(a);
    }
}
void SongPluginManager::setPopupMenu(QMenu* menu, QActionGroup* group)
{
    int i= 0;
    /* foreach(SongListInterface * op, m_songlistpluginList)
     {
             if(op->getAction())
             {
                 QAction* tmp=op->getAction();
                 group->addAction(tmp);
                 tmp->setData(i);
                 menu->addAction(op->getAction());
             }
             i++;
     }*/
}

void SongPluginManager::playingStopped()
{
    foreach(SongInterface* op, m_actionList)
    {
        op->stopped();
    }
}
void SongPluginManager::selectionURI(QStringList list) {}

void SongPluginManager::setmenu(QMenu* menu)
{
    foreach(SongInterface* op, m_actionList)
    {
        if(op->getAction())
            menu->addAction(op->getAction());
    }
    /*  foreach(SongListInterface * op, m_songlistpluginList)
      {
              if(op->getAction())
                  menu->addAction(op->getAction());

      }*/
}
void SongPluginManager::setDock()
{
    foreach(SongInterface* op, m_actionList)
    {
        if(op->hasUI())
        {
            m_mainwindow->addDockWidget(op->orientation(), op->getWidget());
        }
    }
}
void SongPluginManager::writeSettings(QSettings& settings)
{
    foreach(SongInterface* op, m_actionList)
    {
        op->writeSetting(settings);
    }
}
void SongPluginManager::readSettings(QSettings& settings)
{
    foreach(SongInterface* op, m_actionList)
    {
        op->readSetting(settings);
    }
}

SongPluginManager* SongPluginManager::instance(QMainWindow* mainwindow)
{
    if(m_instance == 0)
    {
        m_instance= new SongPluginManager(mainwindow);
    }
    return m_instance;
}

SongInterface* SongPluginManager::m_action(QString opName)
{
    foreach(SongInterface* op, m_actionList)
    {
        if(op->getName() == opName)
        {
            return op;
        }
    }
    return 0;
}
