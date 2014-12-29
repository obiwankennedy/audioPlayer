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
private:
    QString m_uri;
};

#endif // MEDIA_H
