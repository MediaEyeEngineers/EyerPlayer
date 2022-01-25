#include "ThreadAudioPlay.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    ThreadAudioPlay::ThreadAudioPlay()
    {

    }

    ThreadAudioPlay::~ThreadAudioPlay()
    {

    }

    void ThreadAudioPlay::Run()
    {
        EyerLog("ThreadAudioPlay Start\n");

        while (!stopFlag) {

        }

        EyerLog("ThreadAudioPlay Stop\n");
    }

    int ThreadAudioPlay::SetStopFlag()
    {
        stopFlag = 1;
        return 0;
    }
}