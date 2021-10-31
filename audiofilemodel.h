/***************************************************************************
 *	Copyright (C) 2020 by Renaud Guezennec                               *
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
#ifndef AUDIOFILEMODEL_H
#define AUDIOFILEMODEL_H

#include <QAbstractListModel>
#include <memory>
#include <vector>

struct AudioFileInfo
{
    QString m_filepath;
    QString m_artist;
    QString m_title;
    quint64 m_time; // in second
};

class AudioFileModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role
    {
        PathRole= Qt::UserRole + 1,
        ArtistRole,
        TitleRole,
        TimeRole,
        IndexRole,
        ExportSelectedRole
    };

    explicit AudioFileModel(QObject* parent= nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex& parent= QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role= Qt::DisplayRole) const override;

    // Add data:
    bool appendSongs(const QList<QVariantMap>& pathlist);

    // Remove data:
    bool removeSongs(const std::vector<int>& songs);

    std::vector<AudioFileInfo*> songs() const;
    AudioFileInfo* songInfoAt(int index) const;

    QHash<int, QByteArray> roleNames() const override;

    void infoUpdated(int i);

    void insertSongAt(int i, const std::vector<QString>& vec);
    void resetModel();

    void addToExport(int i);
    void cleanExportList();

    const std::vector<int>& exportList() const;

private:
    std::vector<std::unique_ptr<AudioFileInfo>> m_data;
    std::vector<int> m_selectedToExport;
};

#endif // AUDIOFILEMODEL_H
