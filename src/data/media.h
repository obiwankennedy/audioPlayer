#ifndef MEDIA_H
#define MEDIA_H

#include <QString>

/**
 * @brief The Media class - should represent any generic media data.
 */
class Media
{
public:
    Media();

    QString getUri() const;

    void setUri(QString uri);



    virtual void readData(QDataStream& data);
    virtual void writeData(QDataStream& data);
protected:
    QString m_uri;
};

#endif // MEDIA_H
