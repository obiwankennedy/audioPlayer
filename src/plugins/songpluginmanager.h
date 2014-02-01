#ifndef SONGPLUGINMANAGER_H
#define SONGPLUGINMANAGER_H

#include <QSettings>
#include <QList>
#include <QMenu>
#include <playlistitem.h>
#include <QMainWindow>
class SongInterface;
class SongListInterface;
class QString;
class QStringList;

class SongPluginManager : public QObject
{

Q_OBJECT

public:
    ~SongPluginManager();

    void show(QString opName);
    static SongPluginManager * instance(QMainWindow* m_mainwindow = NULL);
    void setmenu(QMenu* menu);
    void setPopupMenu(QMenu* menu,QActionGroup* group);
    void writeSettings(QSettings& settings);
    void readSettings(QSettings& settings);
    void displayPreviousState();


private:
    SongPluginManager(QMainWindow* mainwindow);
    SongInterface * m_action( QString opName );
    void SetSong(QString opName,PlaylistItem* p);
    QString getName();

public slots:
     void playingSongChanged(SongFields* a);
     void selectionURI(QStringList list);
     void playingStopped();
     void setDock();

private:
    QList<SongInterface *> m_actionList;
    QList<SongListInterface *> m_songlistpluginList;
    static SongPluginManager * m_instance;
    QMainWindow* m_mainwindow;
};


#endif // SONGPLUGINMANAGER_H
