#ifndef EYERPLAYER_DECODEQUEUE_HPP
#define EYERPLAYER_DECODEQUEUE_HPP

#include "EyerAV/EyerAV.hpp"

namespace Eyer
{
    class DecodeQueue
    {
    public:
        

        virtual int PutPacket(EyerAVPacket & packet) = 0;
        virtual int GetFrame(EyerAVFrame & frame) = 0;
    };
}

#endif //EYERPLAYER_DECODEQUEUE_HPP
