#include <QToolBar>
#include <QtGui>
#include <random>

#include "player.h"
#include <QFile>
#include <QVariant>
//
#include <QtSvg>

Player::Player(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
    m_current= NULL;
    last= NULL;

#ifdef REPEAT
    m_repeatCheck= false;
#endif
    m_mediaPlayer= new QMediaPlayer();
    connect(
        m_mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(playerStatusChanged(QMediaPlayer::State)));
    connect(m_mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this,
        SLOT(statusChanged(QMediaPlayer::MediaStatus)));

    connect(m_mediaPlayer, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(sourceChanged(QMediaContent)));
    mypreference= Preference_data::getInstance();
    myPlaylist= Playlist::getInstance();
    m_listposition= -1;
    position= 0;
    selectedReadMode= mypreference->getSelectedReadMode();

    setupActions();

    // readSettings();
    setupUi();
    m_seekSlider->setMaximum(0);
}

void Player::setupUi()
{
    //	QTextStream out(stderr,QIODevice::WriteOnly);

    QToolBar* bar= new QToolBar;
    bar->setStyleSheet("QToolBar { border: 0px }");
    bar->addAction(previousAction);
    bar->addAction(playAction);

    bar->addAction(pauseAction);
    bar->addAction(stopAction);
    bar->addAction(nextAction);
    bar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_seekSlider= new QSlider(this);

    m_pictureLabel= new QLabel();
    m_pictureLabel->setMaximumHeight(150);
    m_pictureLabel->setMaximumWidth(150);
    m_pictureLabel->setScaledContents(true);
    QHBoxLayout* m_horizonLayout= new QHBoxLayout();

    m_horizonLayout->addWidget(m_pictureLabel);

    m_seekSlider->setOrientation(Qt::Horizontal);
    connect(this, SIGNAL(positionTime(int)), m_seekSlider, SLOT(setValue(int)));
    connect(m_mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(tick(qint64)));
    connect(m_seekSlider, SIGNAL(sliderMoved(int)), this, SLOT(setTime(int)));
    connect(m_mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(setDuration(qint64)));

    QToolBar* bar2= new QToolBar;
    bar2->addWidget(randomly);
    bar2->setStyleSheet("QToolBar { border: 0px }");
    m_volumeSlider= new QSlider(this);
    m_volumeSlider->setOrientation(Qt::Horizontal);
    m_volumeSlider->setRange(0, 100);
    connect(m_volumeSlider, SIGNAL(valueChanged(int)), m_mediaPlayer, SLOT(setVolume(int)));
    m_volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);

    m_timeLcd= new QLCDNumber;
    m_timeLcd->setPalette(palette);
    m_timeLcd->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    title= new QLineEdit;
    title->setReadOnly(true);
#ifdef REPEAT
    m_repeatCheck= new QCheckBox(tr("Repeat:"), this);
    connect(m_repeatCheck, SIGNAL(clicked()), this, SLOT(setRepeat()));
    m_repeatCheck->setChecked(m_repeatState);
#endif
    QHBoxLayout* seekerLayout= new QHBoxLayout;
    seekerLayout->setMargin(0);
    // seekerLayout->setPadding(0);
    seekerLayout->addWidget(m_seekSlider);
    seekerLayout->addWidget(m_timeLcd);

    QHBoxLayout* playbackLayout= new QHBoxLayout;
    playbackLayout->setMargin(0);
    // playbackLayout->setPadding(0);
    playbackLayout->addWidget(bar);
    playbackLayout->addWidget(title);
    playbackLayout->addWidget(bar2);
#ifdef REPEAT
    playbackLayout->addWidget(m_repeatCheck);
#endif
    playbackLayout->addStretch();
    playbackLayout->addWidget(m_volumeSlider);

    QVBoxLayout* mainLayout= new QVBoxLayout;
    mainLayout->setMargin(0);
    //  mainLayout->setPadding(0);
    mainLayout->addLayout(seekerLayout);
    mainLayout->addLayout(playbackLayout);

    m_horizonLayout->addLayout(mainLayout);
    setLayout(m_horizonLayout);
}

void Player::playerStatusChanged(QMediaPlayer::State state)
{
    switch(state)
    {
    case QMediaPlayer::StoppedState:
        stopAction->setEnabled(false);
        playAction->setEnabled(true);
        pauseAction->setEnabled(false);
        m_seekSlider->setValue(0);
        m_seekSlider->setEnabled(false);
        m_timeLcd->display("00:00");
        break;
    case QMediaPlayer::PlayingState:
        playAction->setEnabled(false);
        pauseAction->setEnabled(true);
        stopAction->setEnabled(true);
        m_seekSlider->setEnabled(true);
        m_seekSlider->setMaximum(m_mediaPlayer->duration());
        break;
    case QMediaPlayer::PausedState:
        pauseAction->setEnabled(false);
        stopAction->setEnabled(true);
        playAction->setEnabled(true);
        // m_seekSlider->setMaximum(0);
        break;
    };
}

void Player::statusChanged(QMediaPlayer::MediaStatus status)
{
    switch(status)
    {
    case QMediaPlayer::InvalidMedia:
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::EndOfMedia:
        next();
        break;
    case QMediaPlayer::BufferingMedia:
        break;
    default:
        break;
    }
}
void Player::tick(qint64 time)
{
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

    m_timeLcd->display(displayTime.toString("mm:ss"));

    if(m_mediaPlayer->duration() != 0)
    {
        // qDebug() << "time:" << time << m_seekSlider->maximum();
        emit positionTime(time);
    }
    else
    {
        next();
    }
    //  out << mediaObject->totalTime() << " " << time << endl;
    //	if(mediaObject->totalTime()==time)
    //		next();
}
#ifdef REPEAT
void Player::setRepeat()
{
    m_repeatState= m_repeatCheck->isChecked();
}
#endif
void Player::sourceChanged(const QMediaContent& media)
{
    if(m_current != NULL)
    {
        setTitle(m_current->getReadableTitle());
        m_current->setReading(true);
        QPixmap* img= new QPixmap();
        img->convertFromImage(m_current->getPicture());
        m_pictureLabel->setPixmap(*img);
        if(m_current->getPicture().isNull())
        {
            m_pictureLabel->setVisible(false);
        }
        else
        {
            m_pictureLabel->setVisible(true);
        }
        emit playingSongChanged(m_current->getFields2());
        if(last != NULL)
        {
            last->setReading(false);
        }
    }
    switch(selectedReadMode)
    {
    case ONEFILE:
        break;
    case SEQUENTIAL:
    {
        emit SetId(position);
        break;
    }
    case RANDOM:
    {
        emit SetId(m_positions[m_listposition]);
        break;
    }
    }

    m_timeLcd->display("00:00");
    m_seekSlider->setRange(0, m_mediaPlayer->duration());
}
void Player::Finish()
{
    if(m_current != NULL)
        setTitle(m_current->getReadableTitle());
}
void Player::setDuration(qint64 last)
{
    m_seekSlider->setMaximum(last);
}

void Player::setFile(const QModelIndex& index)
{
    if(!index.isValid())
        return;

    last= m_current;
    position= index.row();
    m_current= (*myPlaylist)[position];

    switch(selectedReadMode)
    {
    case ONEFILE:
    case SEQUENTIAL:
    {
        break;
    }
    case RANDOM:
    {
        m_positions.insert(++m_listposition, position);
        break;
    }
    }

    setTitle(m_current->getReadableTitle());
    QMediaContent* source= playSong(m_current);
    m_mediaPlayer->setMedia(*source);
    m_mediaPlayer->play();
}
void Player::setupActions()
{
    playAction= new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAction->setShortcut(Qt::Key_Space);
    playAction->setDisabled(true);
    pauseAction= new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    pauseAction->setShortcut(tr("Ctrl+A"));
    pauseAction->setDisabled(true);
    stopAction= new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAction->setShortcut(tr("Ctrl+K"));
    stopAction->setDisabled(true);

    nextAction= new QAction(style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
    nextAction->setShortcut(tr("N"));
    previousAction= new QAction(style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
    previousAction->setShortcut(tr("P"));
    QList<QByteArray> list= QImageReader::supportedImageFormats();
    /*  foreach(QByteArray tmp, list)
      {
          qDebug() << tmp;
      }
  */
    randomly= new QPushButton(QIcon(":/resources/pixmaps/Infinite.svg"), tr(""), this);
    randomly->setFlat(true);
    randomly->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    randomly->setCheckable(true);
    (mypreference->getSelectedReadMode() == RANDOM) ? randomly->setChecked(true) : randomly->setChecked(false);

    connect(playAction, SIGNAL(triggered()), m_mediaPlayer, SLOT(play()));
    connect(randomly, SIGNAL(toggled(bool)), this, SLOT(setRandom(bool)));
    connect(pauseAction, SIGNAL(triggered()), m_mediaPlayer, SLOT(pause()));
    connect(stopAction, SIGNAL(triggered()), m_mediaPlayer, SLOT(stop()));
    connect(stopAction, SIGNAL(triggered()), this, SIGNAL(playingStop()));
    connect(nextAction, SIGNAL(triggered()), this, SLOT(next()));
    connect(previousAction, SIGNAL(triggered()), this, SLOT(previous()));
}
QMediaContent* Player::playSong(PlaylistItem* p)
{
    // QFile* file = new QFile(p->getURI());
    if(QFile::exists(p->getURI()))
    {
        return new QMediaContent(QUrl::fromLocalFile(p->getURI()));
    }
    else
    {
        next();
        return playSong(m_current);
    }
}
void Player::next()
{
    last= m_current;
    selectedReadMode= mypreference->getSelectedReadMode();

    QMediaContent* source= NULL;

    switch(selectedReadMode)
    {
    case ONEFILE:
#ifdef REPEAT
        if(m_repeatState)
        {
            source= playSong(current);
            break;
        }
#endif
    case SEQUENTIAL:
    {
        if(position + 1 < myPlaylist->size())
        {
            m_current= (*myPlaylist)[++position];
            source= playSong(m_current);
        }
        break;
    }
    case RANDOM:
    {
        int place= 0;
        if(m_listposition == m_positions.size() - 1)
        {
            std::random_device rd;
            std::uniform_int_distribution<int> dist(0, myPlaylist->size() - 1);
            place= dist(rd); //(int)((double)rand() / ((double)RAND_MAX + 1) * myPlaylist->size());
            m_positions << place;
            ++m_listposition;
        }
        else if(m_listposition + 1 < m_positions.size())
        {
            place= m_positions[m_listposition + 1];
            ++m_listposition;
        }
        else
        {
            place= m_positions.last();
            m_listposition= m_positions.size() - 1;
        }

        m_current= (*myPlaylist)[place];
        source= playSong(m_current);

        break;
    }
    default:
    {
        selectedReadMode= RANDOM;
        int place;
        if(m_listposition == m_positions.size() - 1)
        {
            place= (int)((double)rand() / ((double)RAND_MAX + 1) * myPlaylist->size());
            m_positions << place;
            ++m_listposition;
        }
        else if(m_listposition + 1 < m_positions.size())
        {
            place= m_positions[m_listposition + 1];
            ++m_listposition;
        }
        else
        {
            place= m_positions.last();
            m_listposition= m_positions.size() - 1;
        }

        m_current= (*myPlaylist)[place];
        source= playSong(m_current);

        break;
    }
    }
    if(m_current != NULL)
    {
        setTitle(m_current->getReadableTitle());
    }
    m_mediaPlayer->setMedia(*source);
    m_mediaPlayer->play();
}
void Player::previous()
{
    // QTextStream out(stderr,QIODevice::WriteOnly);
    last= m_current;
    selectedReadMode= mypreference->getSelectedReadMode();
    QMediaContent* source= NULL;

    switch(selectedReadMode)
    {
    case ONEFILE:
    case SEQUENTIAL:
    {
        m_current= (*myPlaylist)[++position];
        source= playSong(m_current);
        ;
        break;
    }
    case RANDOM:
    {
        // int pos = (int)((double)rand() / ((double)RAND_MAX + 1) * myPlaylist->size())

        int place= 0;
        if(m_listposition >= 1)
        {
            place= m_positions.at(--m_listposition);
        }
        else
        {
            place= (int)((double)rand() / ((double)RAND_MAX + 1) * myPlaylist->size());
            m_positions.insert(0, place);
            m_listposition= 0;
        }

        m_current= (*myPlaylist)[place];
        source= playSong(m_current);

        break;
    }
    }
    if(m_current != NULL)
    {
        setTitle(m_current->getReadableTitle());
    }
    m_mediaPlayer->setMedia(*source);
    m_mediaPlayer->play();
}

QString Player::getTitle()
{
    return title->text();
}

void Player::setTitle(QString value)
{
    title->setText(value);
}

void Player::setRandom(bool toggle)
{
    if(toggle)
    {
        mypreference->setSelectedReadMode(RANDOM);
    }
    else
    {
        mypreference->setSelectedReadMode(SEQUENTIAL);
    }
}
/// public API for DBUS
void Player::nextSong()
{
    next();
}
void Player::previousSong()
{
    previous();
}
void Player::pauseSong()
{
    m_mediaPlayer->pause();
}
void Player::playSong()
{
    m_mediaPlayer->play();
}
void Player::setSelectionMode(int mode)
{
    mypreference->setSelectedReadMode(mode);
}

void Player::stopSong()
{
    m_mediaPlayer->stop();
}

void Player::increaseSong(int i)
{
    QMediaContent* source= NULL;
    int pos= playListItem2Index(m_current);
    pos+= i;
    if(pos >= myPlaylist->size())
    {
        pos= myPlaylist->size() - 1;
    }

    m_current= (*myPlaylist)[pos];
    source= playSong(m_current);

    if(m_current != NULL)
        setTitle(m_current->getReadableTitle());

    m_mediaPlayer->setMedia(*source);
    m_mediaPlayer->play();
}

void Player::decreaseSong(int i)
{
    QMediaContent* source= NULL;
    int pos= playListItem2Index(m_current);
    pos-= i;
    if(pos < 0)
    {
        pos= 0;
    }

    m_current= (*myPlaylist)[pos];
    source= playSong(m_current);

    if(m_current != NULL)
        setTitle(m_current->getReadableTitle());

    m_mediaPlayer->setMedia(*source);
    m_mediaPlayer->play();
}
void Player::setVolume(int vol)
{
    qreal vol2= (qreal)vol / 100;
    m_mediaPlayer->setVolume(vol2);
}
void Player::seek(QString) {}
int Player::playListItem2Index(PlaylistItem* current)
{
    return myPlaylist->item2index(current);
}

void Player::stopAndClear()
{
    m_mediaPlayer->stop();
    m_mediaPlayer->setMedia(QMediaContent());
}

void Player::readSettings(QSettings& settings)
{
    // QSettings settings("Renaud Guezennec", "player");

    for(int i= mypreference->getHistorySong(); (i > -1); i--)
    {
        int temp= settings.value(QString().setNum(i), -1).toInt();
        if(temp > -1)
        {
            m_positions.append(temp);
        }
    }
    if(!m_positions.empty())
    {
        m_listposition= m_positions.size() - 1;
        int a= m_positions.last();
        if(a < myPlaylist->size())
        {
            m_current= (*myPlaylist)[a];
            if(m_current != NULL)
            {
                QMediaContent source= QMediaContent(QUrl::fromLocalFile(m_current->getURI()));
                setTitle(m_current->getReadableTitle());
                m_mediaPlayer->setMedia(source);
                sourceChanged(source);
                playAction->setEnabled(true);
                emit SetId(m_positions[m_listposition]);
            }
        }
    }
#ifdef REPEAT
    m_repeatState= settings.value("repeat", m_repeatState).toBool();
#endif

    m_current= new PlaylistItem();
    QString uri= settings.value("currentSong").value<QString>();
    m_current->setURI(uri);

    m_mediaPlayer->setVolume(settings.value("volume", m_mediaPlayer->volume()).toInt());
    m_volumeSlider->setValue(m_mediaPlayer->volume());
}
void Player::writeSettings(QSettings& settings)
{
    // QSettings settings("Renaud Guezennec", "player");

    for(int i= 0; ((i <= mypreference->getHistorySong()) && (i < m_positions.size())); i++)
    {
        settings.setValue(QString(i), m_positions[m_positions.size() - (1 + i)]);
    }
    if(NULL != m_current)
    {
        settings.setValue("currentSong", m_current->getURI());
    }
#ifdef REPEAT
    settings.setValue("repeat", m_repeatState);
#endif
    settings.setValue("volume", m_mediaPlayer->volume());
}
void Player::setTime(int time)
{
    m_mediaPlayer->setPosition(time);
}
void Player::showEvent(QShowEvent* event)
{
    /*if(NULL!=m_current)
        playSong(m_current);*/

    QWidget::showEvent(event);
}

// void Player::setVisible(bool visible)
//{
//    if(NULL!=m_current)
//     playSong(m_current);

//    QWidget::setVisible(visible);
//}
