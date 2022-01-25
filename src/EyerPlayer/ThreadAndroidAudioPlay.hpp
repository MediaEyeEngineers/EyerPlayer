#ifndef EYERPLAYERANDROID_THREADANDROIDAUDIOPLAY_HPP
#define EYERPLAYERANDROID_THREADANDROIDAUDIOPLAY_HPP

#include "ThreadAudioPlay.hpp"

namespace Eyer
{
    class ThreadAndroidAudioPlay : public ThreadAudioPlay
    {
    public:
        virtual void Run() override;
        virtual int SetStopFlag() override;
    };
}

#endif //EYERPLAYERANDROID_THREADANDROIDAUDIOPLAY_HPP
