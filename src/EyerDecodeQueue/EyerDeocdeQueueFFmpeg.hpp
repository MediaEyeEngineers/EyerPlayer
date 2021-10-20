#ifndef EYERPLAYER_EYERDEOCDEQUEUEFFMPEG_HPP
#define EYERPLAYER_EYERDEOCDEQUEUEFFMPEG_HPP

#include "EyerDeocdeQueue.hpp"
#include "FFmpegDecodeThread.hpp"

namespace Eyer
{
    class EyerDeocdeQueueFFmpeg : public EyerDeocdeQueue
    {
    public:
        EyerDeocdeQueueFFmpeg(const EyerAVStream & stream);
        ~EyerDeocdeQueueFFmpeg();

        virtual int Start() override;
        virtual int Stop() override;
        virtual int PutPacket(EyerAVPacket & packet) override;

    private:
        FFmpegDecodeThread * decodeThread = nullptr;
    };
}

#endif //EYERPLAYER_EYERDEOCDEQUEUEFFMPEG_HPP
