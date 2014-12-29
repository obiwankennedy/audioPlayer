#ifndef PL_LISTVIEW_H
#define PL_LISTVIEW_H

#include <QListView>
#include "playlistitem.h"
#include "pl_abstractListViewer.h"

class PL_ListView : public QListView, public PL_AbstractListViewer
{
    Q_OBJECT
public:
    PL_ListView(QWidget * p = NULL);
    virtual bool hasCopyPasteSupport() const;
    virtual bool isTabVisible() const;
    virtual QString tabTitle() const;
    virtual void displayMenu(QMenu* menu);


    virtual void readSettings(QSettings& settings);
    virtual void writeSettings(QSettings& settings);
    virtual QList<PlaylistItem*>* getSelectedItem();
    virtual QList<int>* getVisibleColumn();
    virtual void aboutToHide();
    virtual void aboutToShow();
 public slots:
    virtual void cancel();
 protected:
    void mouseDoubleClickEvent(QMouseEvent*);
    bool m_closed;
signals:
    void dataModelChanged();
    void playSong(PlaylistItem*);
};

#endif // PL_LISTVIEW_H
