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
#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <QMediaContent>
#include <QMediaPlayer>
#include <QObject>
#include <QPointer>

#include "filteredmodel.h"

#include <deque>
#include <memory>

class AudioFileModel;
class CommandServer;
class FilteredModel;
class AudioController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int songIndex READ songIndex WRITE setSongIndex NOTIFY songIndexChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(PlayingMode mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(qint64 seek READ seek WRITE setSeek NOTIFY seekChanged)
    Q_PROPERTY(AudioFileModel* model READ model NOTIFY modelChanged)
    Q_PROPERTY(bool playing READ isPlaying NOTIFY playingChanged)
    Q_PROPERTY(FilteredModel* filteredModel READ filteredModel CONSTANT)
public:
    enum PlayingMode
    {
        LOOP,
        UNIQUE,
        NEXT,
        SHUFFLE
    };
    Q_ENUM(PlayingMode)
    AudioController(QObject* parent= nullptr);
    ~AudioController() override;

    int songIndex() const;
    PlayingMode mode() const;
    int volume() const;
    qint64 seek() const;
    AudioFileModel* model() const;
    qint64 duration() const;
    QString title() const;
    bool isPlaying() const;
    FilteredModel* filteredModel() const;
    void resetModel() const;

public slots:
    void setSongIndex(int song);
    void setMode(PlayingMode mode);
    void setVolume(int vol);
    void setSeek(qint64 move);

    void play();
    void pause();
    void next();
    void previous();
    void find(const QString& text);

signals:
    void songIndexChanged();
    void modeChanged();
    void volumeChanged();
    void seekChanged();
    void modelChanged();
    void durationChanged(qint64 duration);
    void titleChanged();
    void playingChanged();

protected:
    void mediaStatus(QMediaPlayer::MediaStatus status);

    void repeatSong();
    void nextInLineSong();
    void shuffleSong();
protected slots:
    void updateContent();

private:
    // QPointer<AudioFileModel> m_model;
    std::unique_ptr<AudioFileModel> m_model;
    std::unique_ptr<CommandServer> m_server;
    std::unique_ptr<FilteredModel> m_filteredModel;
    PlayingMode m_mode= SHUFFLE;
    QMediaPlayer m_player;
    QMediaContent m_content;
    int m_duration;
    QString m_title;
    int m_pos= 0;
    std::deque<int> m_previousIndex;
};

#endif // AUDIOCONTROLLER_H
