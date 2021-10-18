#ifndef EYERPLAYER_DECODEQUEUEVIDEO_HPP
#define EYERPLAYER_DECODEQUEUEVIDEO_HPP

#include "DecodeQueue.hpp"

namespace Eyer
{
    class DecodeQueueVideo : public DecodeQueue
    {
    public:
        virtual int PutPacket(EyerAVPacket & packet) = 0;
        virtual int GetFrame(EyerAVFrame & frame) = 0;
    };
}

#endif //EYERPLAYER_DECODEQUEUEVIDEO_HPP
