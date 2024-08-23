#ifndef PREFERENCES_IMPL_H
#define PREFERENCES_IMPL_H
//
#include <QDialog>
#include <QMap>
#include <QList>
#include <QTextCodec>
#include "playlistviewer.h"
#include "ui_preferences.h"
#include "preference_data.h"
//
class Preferences_Impl_Dialog : public QDialog, public Ui::Preferences
{
Q_OBJECT
	QList<QTextCodec *> codecs;
	Preference_data* mypreference;
	QList<QCheckBox*> filterscb;
        PlayListViewer* m_tabs;
public:
        Preferences_Impl_Dialog(PlayListViewer* tabs ,QWidget * parent = 0, Qt::WindowFlags f = 0 );
	void findCodecs();
	void setCodecList(const QList<QTextCodec *> &list);
private slots:
 	void defaultfolderchooser();
   	void apply(QAbstractButton * button);
   	void Modified();
    void doc_browserchooser();
    void onCurrentBehaviourChanged(int);
    void onCurrentViewerChanged(int  );
signals:
	void Modify();
};
#endif





