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
    AudioFormat,
    AudioModel
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
constexpr auto artiste{"artiste"};
constexpr auto title{"title"};
constexpr auto time{"time"};
constexpr auto index{"index"};
}
// ServiceName
constexpr auto audio{"Audio"};

// Action
constexpr auto model{"Model"};
constexpr auto next{"next"};
constexpr auto previous{"previous"};
constexpr auto play{"play"};
constexpr auto stop{"stop"};
constexpr auto random{"random"};
constexpr auto loop{"loop"};
constexpr auto select{"select"};
constexpr auto format{"format"};

//field
constexpr auto sampleRate{"sampleRate"};
constexpr auto channelCount{"channelCount"};
constexpr auto sampleFormat{"sampleFormat"};
}
#endif // CONSTANTS_H
