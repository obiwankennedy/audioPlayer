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
