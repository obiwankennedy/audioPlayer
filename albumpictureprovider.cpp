/***************************************************************************
 *	Copyright (C) 2021 by Renaud Guezennec                               *
 *   http://www.rolisteam.org/contact                                      *
 *                                                                         *
 *   This software is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "albumpictureprovider.h"

#include <QDebug>

AlbumPictureProvider::AlbumPictureProvider() : QQuickImageProvider(QQmlImageProviderBase::Image) {}

void AlbumPictureProvider::setCurrentImage(const QImage& img, const QString& id)
{
    m_expectedId= id;
    m_currentImage= img;
}

QImage AlbumPictureProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)
    if(id == m_expectedId)
        return m_currentImage.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);
    else
        return {};
}
