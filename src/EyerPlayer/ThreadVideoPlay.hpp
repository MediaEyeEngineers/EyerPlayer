#ifndef EYERPLAYERANDROID_THREADVIDEOPLAY_HPP
#define EYERPLAYERANDROID_THREADVIDEOPLAY_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerThread/EyerThreadHeader.hpp"

namespace Eyer
{
    class ThreadVideoPlay
    {
    public:
        int GetVideoFrameQueueSize();
        int PutVideoFrame(EyerAVFrame *);
        EyerAVFrame * GetVideoFrame();
    public:
        Eyer::EyerObserverQueue<EyerAVFrame *> videoFrameQueue;
    };
}

#endif //EYERPLAYERANDROID_THREADVIDEOPLAY_HPP
