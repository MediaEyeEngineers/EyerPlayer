#include "ThreadAndroidAudioPlay.hpp"

namespace Eyer
{
    void ThreadAndroidAudioPlay::Run()
    {
        EyerLog("ThreadAndroidAudioPlay Start\n");
        EyerLog("ThreadAndroidAudioPlay End\n");
    }

    int ThreadAndroidAudioPlay::SetStopFlag()
    {
        stopFlag = 1;
        return 0;
    }
}