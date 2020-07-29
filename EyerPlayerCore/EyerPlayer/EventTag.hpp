#ifndef	EYER_PLAYER_EVENT_TAG_H
#define	EYER_PLAYER_EVENT_TAG_H

#include "EyerCore/EyerCore.hpp"

namespace EyerPlayer {
    class EventTag
    {
    public:
        static const Eyer::EyerString PLAYER;
        static const Eyer::EyerString EVENT_MANAGER;
        static const Eyer::EyerString EVENT_AVREADER;
        static const Eyer::EyerString EVENT_AVDECODER;
        static const Eyer::EyerString EVENT_PLAYER_CTR;
        static const Eyer::EyerString EVENT_AUDIO_PLAYER;

        static const Eyer::EyerString FRAME_QUEUE_PLAYER_VIDEO;
        static const Eyer::EyerString FRAME_QUEUE_PLAYER_AUDIO;
        static const Eyer::EyerString FRAME_QUEUE_DECODER_VIDEO;
    };
}

#endif