#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQmlEngine>
#include <memory>

#include "ClientController.h"
#include "audiocontroller.h"

class MainController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(AudioController* audioCtrl READ audioCtrl CONSTANT)
    Q_PROPERTY(ClientController* clientCtrl READ clientCtrl CONSTANT)
    Q_PROPERTY(PlayingMode mode READ mode WRITE setPlayingMode NOTIFY playingModeChanged FINAL)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged FINAL)
    Q_PROPERTY(bool syncWithServer READ syncWithServer WRITE setSyncWithServer NOTIFY syncWithServerChanged FINAL)
    Q_PROPERTY(QString artist READ artist NOTIFY currentSongChanged)
    Q_PROPERTY(QString title READ title NOTIFY currentSongChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY currentSongChanged)
    Q_PROPERTY(qint64 index READ index NOTIFY currentSongChanged)
    Q_PROPERTY(bool hasImage READ hasImage NOTIFY currentSongChanged FINAL)
    Q_PROPERTY(QImage image READ image NOTIFY currentSongChanged FINAL)
public:
    enum PlayingMode {
        Shuffle,
        Unique,
        Loop,
        Forward
    };
    Q_ENUM(PlayingMode)

    explicit MainController(QObject *parent = nullptr);

    AudioController *audioCtrl() const;
    ClientController *clientCtrl() const;


    MainController::PlayingMode mode() const;

    bool syncWithServer() const;
    void setSyncWithServer(bool newSyncWithServer);

    qreal position() const;
    void setPosition(qreal newPosition);

    QString artist() const;

    QString title() const;

    qint64 duration() const;

    qint64 index() const;

    QImage image() const;

    bool hasImage() const;

public slots:
    void play(int index = -1);
    void previous();
    void next();
    void stop();
    void pause();
    void setPlayingMode(MainController::PlayingMode mode);


signals:
    void playingModeChanged();
    void syncWithServerChanged();
    void positionChanged();

    void currentSongChanged();

private:
    std::unique_ptr<AudioController> m_audioCtrl;
    std::unique_ptr<ClientController> m_clientCtrl;
    MainController::PlayingMode m_mode;
    bool m_syncWithServer{false};
    qint64 m_position{0};
    QString m_artist;
    QString m_title;
    qint64 m_duration;
    qint64 m_index;
    QImage m_img;
    QImage m_image;
    bool m_hasImage;
};

#endif // MAINCONTROLLER_H
