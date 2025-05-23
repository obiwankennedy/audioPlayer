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
#ifndef FILTEREDMODEL_H
#define FILTEREDMODEL_H

#include <QSortFilterProxyModel>
#include <QQmlEngine>

class TagFilteredModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TagFilteredModel(QObject* parent= nullptr);

    int songIndexToSource(int songIndex);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

public slots:
    void addTag(const QString& tag, bool forbidden = false);
    void removeTag(const QString& tag, bool forbidden = false);


private:
    QSet<QString> m_allowed;
    QSet<QString> m_forbidden;
};

class FilteredModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit FilteredModel(QObject* parent= nullptr);

    QString search() const;
    void setSearch(const QString& search);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    QString m_search;
};

#endif // FILTEREDMODEL_H
