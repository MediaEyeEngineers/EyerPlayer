#ifndef EYERPLAYER_EYERPLAYEREVENT_PLAY_HPP
#define EYERPLAYER_EYERPLAYEREVENT_PLAY_HPP

#include "EyerPlayerEvent.hpp"

namespace Eyer
{
    class EyerPlayerEvent_Play : public EyerPlayerEvent
    {
    public:
        EyerPlayerEvent_Play();
        ~EyerPlayerEvent_Play();

        EyerString url;
    };
}

#endif //EYERPLAYER_EYERPLAYEREVENT_PLAY_HPP
