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
#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QAbstractItemModel>
#include <QObject>
#include <QQmlEngine>
#include <QQmlParserStatus>
#include <QStringList>
#include <memory>

#include "audiocontroller.h"
#include "audiofilemodel.h"
#include "filteredmodel.h"

class MainController : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(QAbstractItemModel* model READ model CONSTANT)
    Q_PROPERTY(AudioFileModel* audioModel READ audioModel CONSTANT)
    Q_PROPERTY(QStringList recentFiles READ recentFiles CONSTANT)
    Q_PROPERTY(FilteredModel* filteredModel READ filteredModel CONSTANT)
    Q_PROPERTY(AudioController* audioCtrl READ audioCtrl CONSTANT)
    Q_PROPERTY(QAbstractItemModel* outputModel READ outputModel CONSTANT)
    Q_PROPERTY(int deviceIndex READ deviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)
    Q_PROPERTY(bool hasVideo READ hasVideo NOTIFY hasVideoChanged FINAL)

public:
    explicit MainController(QObject* parent);
    MainController(const MainController&) = delete;
    MainController(MainController&&) = delete;
    MainController& operator=(const MainController&) = delete;
    MainController& operator=(MainController&&) = delete;
    virtual ~MainController() override;

    QString filename() const { return m_filename; }
    QStringList recentFiles() const;

    FilteredModel* filteredModel() const;
    AudioController* audioCtrl() const;

    QAbstractItemModel* model() const;
    AudioFileModel* audioModel() const;

    void saveSettings();

    QAbstractItemModel* outputModel() const;
    int deviceIndex() const;

    bool hasVideo() const;

    static MainController* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

public slots:
    void addFiles(const QList<QUrl>& file, int idx);
    void addDirectory(int idx, const QString& url);
    // void exploreDir(const QString& path);
    void saveFile();
    void loadFile();
    void resetData();
    void setFilename(QString filename);
    void addToExport(int songIndex);
    void resetExport();
    void exportList();
    void removeSelection();
    void setDeviceIndex(int index);

signals:
    void filenameChanged(QString filename);
    void deviceIndexChanged();
    void hasVideoChanged();
    void stateChanged(const QMediaPlayer::PlaybackState& state);

protected:
    void loadSettings();

private:
    QString m_filename;
    std::unique_ptr<AudioController> m_audioCtrl;
    QStringList m_recentFiles;
};

#endif // MAINCONTROLLER_H
