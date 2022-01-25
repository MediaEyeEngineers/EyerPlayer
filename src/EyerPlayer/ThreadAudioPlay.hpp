#ifndef EYERPLAYERANDROID_THREADAUDIOPLAY_HPP
#define EYERPLAYERANDROID_THREADAUDIOPLAY_HPP

#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class ThreadAudioPlay : public EyerThread
    {
    public:
        ThreadAudioPlay();
        ~ThreadAudioPlay();

        virtual void Run() override;
        virtual int SetStopFlag() override;
    };
}

#endif //EYERPLAYERANDROID_THREADAUDIOPLAY_HPP
