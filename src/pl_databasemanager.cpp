#include "pl_databasemanager.h"
#include "playlist.h"

#include <QDebug>

PL_DataBaseManager::PL_DataBaseManager()
{
        m_playlist = Playlist::getInstance();
        m_db = new QSqlDatabase;
        (*m_db) = QSqlDatabase::addDatabase("QPSQL");
        m_db->setHostName("localhost");
        m_db->setDatabaseName("playlistgenerator");
        m_db->setUserName("renaud");
        m_db->setPassword("hulan8ye");
        m_db->setPort(5433);
        m_connectionIsOK = m_db->open();
        m_field << "id" << "position" << "uri" << "artist" << "album" << "comment" << "lyrics" << "year" << "duration" << "genre"
                               << "bitrate" << "Other" << "piste";

}

void PL_DataBaseManager::WriteList()
{
    QSqlQuery query=  QSqlQuery ( *m_db );

    PlaylistItem* tmp=NULL;

    for(int i = 0;i<m_playlist->size();i++)
    {
        tmp = m_playlist->value(i);
        /*query.prepare("Insert into mediafile (id, position, uri, title,artist,album, comment,lyrics,year,duration,genre,bitrate,piste)"
                      "VALUES (nextval(\'mediafile_id_seq\'), :position, :uri,:title, :artist,:album, :comment,:lyrics,:year,:duration,:genre,:bitrate,:piste)");
        */


QString sql = "Insert into mediafile (id, position, uri, title,artist,album, comment,lyrics,year,duration,genre,bitrate,piste) VALUES (nextval(\'mediafile_id_seq\'),%1, \'%2\',\'%3\', \'%4\',\'%5\',\'%6\',\'%7\',%8,%9,%10,%11,%12)";

QString ressql = sql.arg(i).arg(tmp->getURI()).arg(tmp->getSong()->getTitle()).arg(tmp->getSong()->getArtistName()).arg(tmp->getSong()->getAlbum()).arg(tmp->getSong()->getComment()).arg(tmp->getSong()->getLyrics()).arg(tmp->getSong()->getYear()).arg(tmp->getSong()->getDuration()).arg(tmp->getSong()->getGenre()).arg(tmp->getSong()->getBitrate()).arg(tmp->getSong()->getTrackNumber());
              query.prepare(ressql);


//query.bindValue(":id","nextval(\'mediafile_id_seq\')" );
        //query.bindValue(":position",i );
        //@uery.bindValue(":uri",tmp->getURI() );
        //query.bindValue(":title",tmp->getMediaFile()->getTitle() );
       /* query.bindValue(":artist",tmp->getFields()->Artist );
        query.bindValue(":album",tmp->getFields()->album );
        query.bindValue(":comment",tmp->getFields()->Comment );
        query.bindValue(":lyrics",tmp->getFields()->lyrics );
        query.bindValue(":year",tmp->getFields()->Year );
        query.bindValue(":genre",tmp->getFields()->genre );
        query.bindValue(":bitrate",tmp->getFields()->Bitrate );
        query.bindValue(":duration",tmp->getFields()->duration);
        query.bindValue(":piste",tmp->getFields()->track );*/
        //qDebug() << "requete=" << ressql;
        query.exec();
        //qDebug() <<query.lastError () ;
    }


m_db->close();

}
void  PL_DataBaseManager::setPlaylist(Playlist* list)
{
    m_playlist = list;
}

void PL_DataBaseManager::readList()
{
    QSqlQuery query=  QSqlQuery ( *m_db );

    query.prepare("SELECT id, position, uri, artist,album, comment,lyrics,year,duration,genre,bitrate,misc,piste from mediafile order by position");
    query.exec();
    while(query.next())
    {
        //for(int i = 0; i < 13;i++)
        //{
            //qDebug() <<query.value(2);
            QString uri=query.value(2).toString();
           // qDebug() << uri;
            m_playlist->addfile(uri);
        //}
    }
   // qDebug() <<query.lastError () ;
}

bool PL_DataBaseManager::isConnected()
{
    return m_connectionIsOK;
}
