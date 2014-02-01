#ifndef PL_DATABASEMANAGER_H
#define PL_DATABASEMANAGER_H
#include <QtSql>

class Playlist;
class PL_DataBaseManager
{
public:
    PL_DataBaseManager();

    void WriteList();
    void readList();
    bool isConnected();

    void setPlaylist(Playlist* list);

private:
    bool m_connectionIsOK;
    QSqlDatabase* m_db;
    QSqlQuery* m_query;
    QStringList m_field;
    Playlist* m_playlist;
};

#endif // PL_DATABASEMANAGER_H
