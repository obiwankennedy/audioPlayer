
#include "preference_data.h"
#include <QCoreApplication>
#include <QLocale>

//
Preference_data::Preference_data()
{
    codecs= QTextCodec::codecForName("UTF-8");
    uri_default= QDir::homePath();
    nb_recentfiles= 5;
    uri_documentation= QCoreApplication::applicationDirPath() + "/../documentation/" + QLocale::system().name()
                       + "/PlayListGenerator.adp";
    loadlastfile= false;
    viewerBehaviors= new QList<ViewerBehaviour>;

#ifndef HAVE_PHONON
    selectedReadMode= SEQUENTIAL;
    disableAudioPlayer= true;
    nb_historysongs= 5;
#else
    disableAudioPlayer= false;
#endif
}
//
Preference_data::~Preference_data() {}
void Preference_data::setSelectedReadMode(int value)
{
    switch(value)
    {
    case 0:
        selectedReadMode= ONEFILE;
        break;
    case 1:
        selectedReadMode= SEQUENTIAL;
        break;
    case 2:
        selectedReadMode= RANDOM;
        break;
    }
}
Preference_data* Preference_data::singleton= NULL;

Preference_data* Preference_data::getInstance()
{
    if(singleton == NULL)
        singleton= new Preference_data;

    return singleton;
}
void Preference_data::kill()
{
    delete singleton;
}
//
QTextCodec* Preference_data::getCodecs()
{
    return codecs;
}

void Preference_data::setCodecs(QTextCodec* value)
{
    codecs= value;
}

int Preference_data::getNb_recentfiles()
{
    return nb_recentfiles;
}

void Preference_data::setNb_recentfiles(int value)
{
    nb_recentfiles= value;
}

QString Preference_data::getUri_default()
{
    return uri_default;
}

void Preference_data::setUri_default(QString value)
{
    uri_default= value;
}
void Preference_data::writeSettings(QSettings& settings)
{
    // QSettings settings("Renaud Guezennec", "preferences");

    settings.setValue("uri", uri_default);
    settings.setValue("recent", nb_recentfiles);
    settings.setValue("codecs", codecs->name());
    settings.setValue("uri_documentation", uri_documentation);
    settings.setValue("OpenOnStart", loadlastfile);
    settings.setValue("disableAudioPlayer", disableAudioPlayer);
    settings.setValue("showPlayerOnStartReading", showPlayerOnStartReading);
    settings.setValue("showPlayerOnStarting", showPlayerOnStarting);
    settings.setValue("selectedReadMode", selectedReadMode);
    settings.setValue("fileassociation", filters);
    settings.setValue("songhistorynumber", nb_historysongs);
    settings.beginGroup("ViewerBehaviours");
    /*foreach(ViewerBehaviour p,*viewerBehaviors)
    {
        settings.setValue("size", size());
    }*/
    settings.endGroup();
}
void Preference_data::readSettings(QSettings& settings)
{
    // QSettings settings("Renaud Guezennec", "preferences");

    uri_default= settings.value("uri", uri_default).toString();
    nb_recentfiles= settings.value("recent", nb_recentfiles).toInt();
    codecs= QTextCodec::codecForName(settings.value("codecs", codecs->name()).toByteArray());
    uri_documentation= settings.value("uri_documentation", uri_documentation).toString();

    loadlastfile= settings.value("OpenOnStart", loadlastfile).toBool();
    showPlayerOnStartReading= settings.value("showPlayerOnStartReading", showPlayerOnStartReading).toBool();
    showPlayerOnStarting= settings.value("showPlayerOnStarting", showPlayerOnStarting).toBool();
    disableAudioPlayer= settings.value("disableAudioPlayer", disableAudioPlayer).toBool();
    setSelectedReadMode(settings.value("selectedReadMode", selectedReadMode).toInt());
    filters= settings.value("fileassociation", filters).toStringList();

    nb_historysongs= settings.value("songhistorynumber", nb_historysongs).toInt();
}
void Preference_data::setHistorySong(int t)
{
    nb_historysongs= t;
}
int Preference_data::getHistorySong()
{
    return nb_historysongs;
}
bool Preference_data::getLoadlastfile()
{
    return loadlastfile;
}

void Preference_data::setLoadlastfile(bool value)
{
    loadlastfile= value;
}

QString Preference_data::getUri_documentation()
{
    return uri_documentation;
}

void Preference_data::setUri_documentation(QString value)
{
    uri_documentation= value;
}

bool Preference_data::getDisableAudioPlayer()
{
    return disableAudioPlayer;
}
QList<ViewerBehaviour>* Preference_data::getViewerBehaviors()
{
    return viewerBehaviors;
}
void Preference_data::setViewerBehaviors(QList<ViewerBehaviour>* vier)
{
    viewerBehaviors= vier;
}

void Preference_data::setDisableAudioPlayer(bool value)
{
    disableAudioPlayer= value;
}

QStringList Preference_data::getFilters()
{
    return filters;
}

void Preference_data::setFilters(QStringList value)
{
    filters= value;
}
