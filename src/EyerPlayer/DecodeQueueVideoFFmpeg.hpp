#ifndef EYERPLAYER_DECODEQUEUEVIDEOFFMPEG_HPP
#define EYERPLAYER_DECODEQUEUEVIDEOFFMPEG_HPP

#include "DecodeQueueVideo.hpp"

namespace Eyer
{
    class DecodeQueueVideoFFmpeg : public DecodeQueueVideo
    {
    public:
        virtual int PutPacket(EyerAVPacket & packet) override;
        virtual int GetFrame(EyerAVFrame & frame) override;
    };
}

#endif //EYERPLAYER_DECODEQUEUEVIDEOFFMPEG_HPP
