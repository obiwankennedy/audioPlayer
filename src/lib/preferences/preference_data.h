#ifndef PREFERENCE_DATA_H
#define PREFERENCE_DATA_H
//
#include <QDir>
#include "data.h"
#include <QTextCodec>
#include <QTextStream>
#include <QSettings>
//
enum ReadingMode{ONEFILE,SEQUENTIAL,RANDOM};
class Preference_data  
{
	int nb_recentfiles;
        int nb_historysongs;
	QTextCodec* codecs;
	QString uri_default;//default folder uri
	bool loadlastfile;
	bool disableAudioPlayer;
	bool showPlayerOnStartReading;
	bool showPlayerOnStarting;
	ReadingMode selectedReadMode;
	QString uri_documentation;
	Preference_data();
	QStringList filters;
        QList<ViewerBehaviour>* viewerBehaviors;
public:
        void setHistorySong(int t);
        int getHistorySong();
	void setFilters( QStringList value);
	QStringList getFilters();
	void setSelectedReadMode( int value);
	ReadingMode getSelectedReadMode() { return selectedReadMode; }
	void setShowPlayerOnStarting( bool value) { showPlayerOnStarting = value; }
	bool getShowPlayerOnStarting() { return showPlayerOnStarting; }
	void setShowPlayerOnStartReading( bool value) { showPlayerOnStartReading = value; }
	bool getShowPlayerOnStartReading() { return showPlayerOnStartReading; }
	void setDisableAudioPlayer( bool value);
	bool getDisableAudioPlayer();
	void setUri_documentation( QString value);
	QString getUri_documentation();
	void setLoadlastfile( bool value);
	bool getLoadlastfile();
	void setUri_default( QString uri_default);
	QString getUri_default();
        QList<ViewerBehaviour>* getViewerBehaviors();
        void setViewerBehaviors(QList<ViewerBehaviour>*);
	
	void setNb_recentfiles( int value);
	int getNb_recentfiles();
	
	void setCodecs( QTextCodec* value);
	QTextCodec* getCodecs();
	
	static Preference_data* getInstance();
	static void kill();
	virtual ~Preference_data();
    void readSettings(QSettings& settings);
    void writeSettings(QSettings& settings);
private:
	static Preference_data* singleton;
};
#endif
