#ifndef LYRICSVIEWERDOCK_H
#define LYRICSVIEWERDOCK_H
#include "ui_lyricsviewer.h"
#include <QDockWidget>
class LyricsViewerDock : public QDockWidget,public Ui_LyricsViewer
{
        Q_OBJECT
public:
    LyricsViewerDock();
    void setLyrics(const QString& a);

    QString getLyrics();
    void clearData();

public slots:
    void setEditatble(bool);

signals:
    void clickOneditable();
    void clickOnOnline();
    void clickOnSave();

};

#endif // LYRICSVIEWERDOCK_H
