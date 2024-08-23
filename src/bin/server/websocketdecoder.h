#ifndef WEBSOCKETDECODER_H
#define WEBSOCKETDECODER_H

#include <QAudioDecoder>
#include <QObject>

class WebSocketDecoder : public QAudioDecoder
{
public:
    WebSocketDecoder();
};

#endif // WEBSOCKETDECODER_H
