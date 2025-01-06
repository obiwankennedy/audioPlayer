#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QHash>
#include <QString>

namespace constants
{

enum Action
{
    PlayAct,
    StopAct,
    NextAct,
    PreviousAct,
    SelectAct,
    LoopAct,
    RandomAct,
    AudioModel,
    VolumeOnAct,
    MuteAct,
    PlayOnServerAct,
    StreamMusicAct,
    NewSongAct,
    SeekAct,
};



namespace json
{
constexpr auto service{"service"};
constexpr auto action{"action"};
constexpr auto parameter{"Audio"};
constexpr auto songs{"songs"};
constexpr auto pattern{"pattern"};
}

namespace info
{

constexpr auto album{"album"};
constexpr auto artist{"artist"};
constexpr auto path{"path"};
constexpr auto title{"title"};
constexpr auto time{"time"};
constexpr auto index{"index"};
constexpr auto value{"value"};
}
// ServiceName
constexpr auto audio{"Audio"};

// Action
constexpr auto model{"Model"};
constexpr auto next{"next"};
constexpr auto previous{"previous"};
constexpr auto play{"play"};
constexpr auto stop{"stop"};
constexpr auto pause{"pause"};
constexpr auto random{"random"};
constexpr auto loop{"loop"};
constexpr auto unique{"unique"};
constexpr auto forward{"forward"};
constexpr auto select{"select"};
constexpr auto format{"format"};
constexpr auto newSong{"newSong"};
constexpr auto volumeOn{"volumeOn"};
constexpr auto mute{"mute"};
constexpr auto streamMusic{"streamMusic"};
constexpr auto playOnServer{"playOnServer"};
constexpr auto seek{"seek"};

//field
constexpr auto sampleRate{"sampleRate"};
constexpr auto channelCount{"channelCount"};
constexpr auto sampleFormat{"sampleFormat"};
constexpr auto uri{"uri"};
}
#endif // CONSTANTS_H
