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
#include <QtGui>
#include "lyricsplugin.h"
#include <QTextStream>
#include <QAction>
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>


#include "lyricsfinder.h"
#include "wikiflyfinder.h"
#include "wikifinder.h"

void LyricsPlugin::SetSong(SongFields* p)
{
    if(p==NULL)
        return;

    m_proc = new QProcess;

    m_p = p;
    if(m_p->lyrics.isEmpty())
    {

        finderleos->setfields(m_p);
        finiderwikifly->setfields(m_p);
        finderwiki->setfields(m_p);
        if((viewer->isVisible()))
         {
            finderleos->search();
            finiderwikifly->search();
            finderwiki->search();
         }
    }
    else
    {

        viewer->setLyrics(m_p->lyrics);
    }
    connect(m_proc, SIGNAL(error(QProcess::ProcessError)),this,SLOT(onError(QProcess::ProcessError)));
}
QString LyricsPlugin::getName()
{
    viewer = new LyricsViewerDock();
    finderleos = new LyricsFinder();
    finderwiki = new WikiFinder();
    finiderwikifly = new WikiFlyFinder();
    connect(finderleos,SIGNAL(lyricsready()),this,SLOT(refresh()));
    connect(finiderwikifly,SIGNAL(lyricsready()),this,SLOT(refresh()));
    connect(finderwiki,SIGNAL(lyricsready()),this,SLOT(refresh()));
    m_p = NULL;
    connect(viewer,SIGNAL(clickOnOnline()),this,SLOT(onlineResearch()));
    connect(viewer,SIGNAL(clickOneditable()),this,SLOT(startEditing()));
    connect(viewer,SIGNAL(clickOnSave()),this,SLOT(saveLyrics()));

    //readSetting();


    return QString("Lyrics");



}
bool LyricsPlugin::hasUI()
{
    return true;
}
void LyricsPlugin::show()
{
    if(NULL!=m_p)
    {
        finderleos->setfields(m_p);
        finderleos->search();
        finiderwikifly->setfields(m_p);
        finiderwikifly->search();

        finderwiki->setfields(m_p);
        finderwiki->search();
    }
    viewer->setVisible(true);
    m_menuAct->setChecked(true);
}
void LyricsPlugin::refresh()
{
    QString* tmp = NULL;
    QString founder="";
    if(finderleos->foundLyrics())
    {
        QString* tmpleos = finderleos->GetLyrics();
        founder="finderleos";
        if((NULL!=tmpleos)&&(!tmpleos->isEmpty()))
        {
            tmp = tmpleos;
        }
    }

    if(finderwiki->foundLyrics())
    {
        QString* tmpfinderwiki = finderwiki->GetLyrics();
        founder="fenderwiki";
        if((NULL!=tmpfinderwiki)&&(!tmpfinderwiki->isEmpty()))
        {
            tmp = tmpfinderwiki;
        }
    }

    if(finiderwikifly->foundLyrics())
    {
        QString* tmpfiniderwikifly = finiderwikifly->GetLyrics();
        founder="finiderwikifly";
        if((NULL!=tmpfiniderwikifly)&&(!tmpfiniderwikifly->isEmpty()))
        {
            tmp = tmpfiniderwikifly;
        }
    }
    //qDebug() << "Lyrics" <<  tmp << founder;
    if((tmp!=NULL)&&(!tmp->isEmpty()))
     {
       // qDebug() << "Lyrics 2" <<  *tmp;
        viewer->setLyrics(*tmp);
    }
}
QDockWidget* LyricsPlugin::getWidget()
{

    return viewer;
}
QAction* LyricsPlugin::getAction()
{
      m_menuAct = new QAction("Show me the lyrics",this);

      m_menuAct->setShortcut(tr("Ctrl+L"));
      m_menuAct->setStatusTip(tr("Try to find and display the lyrics"));
      connect(m_menuAct, SIGNAL(triggered()), this, SLOT(show()));
      return m_menuAct;
}
bool LyricsPlugin::isVisible()
{
    return viewer->isVisible();
}
void LyricsPlugin::locationChanged(Qt::DockWidgetArea area)
{
    m_currentArea = area;
}

Qt::DockWidgetArea LyricsPlugin::orientation()
{
    return m_currentArea;
}
void LyricsPlugin::readSetting(QSettings& settings)
{

    //QSettings settings("Renaud Guezennec", "lyricsplugin");
    settings.beginGroup("lyricsplugin");
    viewer->setVisible(settings.value("lyricsplugin/visible", viewer->isVisible()).toBool());


    m_currentArea = (Qt::DockWidgetArea)settings.value("lyricsplugin/orientation", Qt::LeftDockWidgetArea).toInt();
     settings.endGroup();

}
void LyricsPlugin::writeSetting(QSettings& settings)
{

   // QSettings settings("Renaud Guezennec", "lyricsplugin");
    settings.beginGroup("lyricsplugin");
    settings.setValue("lyricsplugin/visible", viewer->isVisible());
    settings.setValue("lyricsplugin/orientation", m_currentArea);
    settings.endGroup();
}
void LyricsPlugin::startEditing()
{
    viewer->setEditatble(true);
}
void LyricsPlugin::saveLyrics()
{
    viewer->setEditatble(false);
    m_p->lyrics = viewer->getLyrics();


}
void LyricsPlugin::onlineResearch()
{
    QString url = QString("http://www.google.fr/#q=%1+%2+lyrics").arg(m_p->Artist).arg(m_p->Title);

    QStringList list;
    list << QString(QUrl(url).toEncoded());
    m_proc->start("/usr/bin/firefox",list);
}

void LyricsPlugin::onError( QProcess::ProcessError error)
{
    qDebug() << error;

}
void LyricsPlugin::stopped()
{

    viewer->clearData();

}
//Q_EXPORT_PLUGIN2(PLG_lyrics, LyricsPlugin);
