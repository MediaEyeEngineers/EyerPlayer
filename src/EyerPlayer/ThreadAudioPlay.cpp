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

    /*
    void ThreadAudioPlay::Run()
    {
        EyerLog("ThreadAudioPlay Start\n");

        while (!stopFlag) {

        }

        EyerLog("ThreadAudioPlay Stop\n");
    }
    */

    int ThreadAudioPlay::GetAudioFrameQueueSize()
    {
        return audioFrameQueue.SizeLock();
    }

    int ThreadAudioPlay::PutAudioFrame(EyerAVFrame * audioFrame)
    {
        audioFrameQueue.Lock();
        audioFrameQueue.Push(audioFrame);
        audioFrameQueue.Unlock();
        return 0;
    }

    EyerAVFrame * ThreadAudioPlay::GetAudioFrame()
    {
        EyerAVFrame * audioFrame = nullptr;
        audioFrameQueue.Lock();
        if(audioFrameQueue.Size() > 0){
            audioFrame = audioFrameQueue.FrontPop();
        }
        audioFrameQueue.Unlock();
        return audioFrame;
    }
    /*
    int ThreadAudioPlay::SetStopFlag()
    {
        stopFlag = 1;
        return 0;
    }
    */
}