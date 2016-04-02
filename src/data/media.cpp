#include "media.h"

Media::Media()
{
}
QString Media::getUri() const
{
    return m_uri;
}

void Media::setUri(QString uri)
{
    m_uri = uri;
}
void Media::readData(QDataStream& data)
{
    data >> m_uri;
}

void Media::writeData(QDataStream& data)
{
    data << m_uri;
}
