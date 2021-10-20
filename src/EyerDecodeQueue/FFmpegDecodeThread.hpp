#ifndef EYERPLAYER_FFMPEGDECODETHREAD_HPP
#define EYERPLAYER_FFMPEGDECODETHREAD_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class FFmpegDecodeThread : public EyerThread
    {
    public:
        virtual void Run() override;
    };
}

#endif //EYERPLAYER_FFMPEGDECODETHREAD_HPP
