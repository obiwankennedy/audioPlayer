#ifndef PL_ABSTRACTLISTVIEWER_H
#define PL_ABSTRACTLISTVIEWER_H
#include "playlistitem.h"
#include <QList>
#include <QSettings>


class PL_AbstractListViewer
{

public:
    virtual bool hasCopyPasteSupport() const  = 0 ;
    virtual bool isTabVisible() const = 0;
    virtual bool isClosed(){return m_closed;}
    virtual QString tabTitle() const = 0;
    virtual void displayMenu(QMenu* menu) = 0;

    virtual void setClosed(bool b) {m_closed = b;}
    virtual void readSettings(QSettings& settings) = 0;
    virtual void writeSettings(QSettings& settings) = 0;
    virtual QList<PlaylistItem*>* getSelectedItem() = 0;
    virtual QList<int>* getVisibleColumn() = 0;
    virtual void aboutToHide() = 0;
    virtual void aboutToShow() = 0;
    virtual void setAvailable(bool aval){m_isAvailable=aval;}
    virtual bool isAvailable(){return m_isAvailable;}
    virtual void setBehaviour(ViewerBehaviour aval){m_behaviour=aval;}
    virtual ViewerBehaviour Behaviour(){return m_behaviour;}
 public slots:
    virtual void cancel() = 0;
signals:


 protected:
    bool m_closed;
    QMenu* internalMenu;
    bool m_stateCopy;
    bool m_stateCut;
    bool m_statePaste;
    bool m_isAvailable; // true if the viewer is in a Tabwidget
    ViewerBehaviour m_behaviour;

};



#endif // PL_ABSTRACTLISTVIEWER_H
