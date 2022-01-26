#ifndef EYERPLAYERANDROID_THREADAUDIOPLAY_HPP
#define EYERPLAYERANDROID_THREADAUDIOPLAY_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerThread/EyerThreadHeader.hpp"

namespace Eyer
{
    class ThreadAudioPlay : public EyerThread
    {
    public:
        ThreadAudioPlay();
        virtual ~ThreadAudioPlay();

        int GetAudioFrameQueueSize();
        int PutAudioFrame(EyerAVFrame *);
        EyerAVFrame * GetAudioFrame();

    private:
        Eyer::EyerObserverQueue<EyerAVFrame *> audioFrameQueue;
    };
}

#endif //EYERPLAYERANDROID_THREADAUDIOPLAY_HPP
