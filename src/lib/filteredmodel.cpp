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

FilteredModel::FilteredModel(QObject* parent) : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
}

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

///////////////////////
/// \brief TagFilteredModel::TagFilteredModel
/// \param parent
//////////////////////
TagFilteredModel::TagFilteredModel(QObject *parent)
{
setDynamicSortFilter(true);
}

bool TagFilteredModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if(m_allowed.isEmpty() && m_forbidden.isEmpty())
        return true;

    QModelIndex index= sourceModel()->index(sourceRow, 0, sourceParent);
    auto title= index.data(AudioFileModel::TitleRole).toString();
    auto tags= index.data(AudioFileModel::TagsRole).toStringList();

    auto isAllowed = [this](const QStringList& tags){
        if(m_allowed.isEmpty())
            return true;
        bool res = false;
        for(auto const& tag : tags)
        {
            if(m_allowed.contains(tag))
                res = true;
        }
        return res;
    };

    auto isForbidden = [this](const QStringList& tags){
              if(m_forbidden.isEmpty())
                  return false;
              bool res = false;
              for(auto const& tag : tags)
              {
                  if(m_forbidden.contains(tag))
                      res = true;
              }
              return res;
    };

    return isAllowed(tags) && !isForbidden(tags);

}

void TagFilteredModel::addTag(const QString &tag, bool forbidden)
{
    if(forbidden)
        m_forbidden.insert(tag);
    else
        m_allowed.insert(tag);

    invalidateFilter();
}

void TagFilteredModel::removeTag(const QString &tag, bool forbidden)
{
    if(forbidden)
        m_forbidden.remove(tag);
    else
        m_allowed.remove(tag);

    invalidateFilter();
}

int TagFilteredModel::songIndexToSource(int songIndex)
{
    auto c = mapToSource(index(songIndex, 0, QModelIndex()));
    qDebug() << "songIndex: " << songIndex << " - " << c.row();
    return c.data(AudioFileModel::IndexRole).toInt();;
}
