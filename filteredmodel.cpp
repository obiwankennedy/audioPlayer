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
#include "filteredmodel.h"

#include "audiofilemodel.h"

FilteredModel::FilteredModel(QObject* parent) : QSortFilterProxyModel(parent) {}

QString FilteredModel::search() const
{
    return m_search;
}

bool FilteredModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    if(m_search.isEmpty())
        return true;
    QModelIndex index= sourceModel()->index(sourceRow, 0, sourceParent);
    auto title= index.data(AudioFileModel::TitleRole).toString();
    auto artist= index.data(AudioFileModel::ArtistRole).toString();
    return title.contains(m_search, Qt::CaseInsensitive) || artist.contains(m_search, Qt::CaseInsensitive);
}

void FilteredModel::setSearch(const QString& search)
{
    m_search= search;
    invalidateFilter();
}
