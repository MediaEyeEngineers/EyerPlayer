#include "ThreadVideoPlay.hpp"

namespace Eyer
{
    int ThreadVideoPlay::GetVideoFrameQueueSize()
    {
        return videoFrameQueue.SizeLock();
    }

    int ThreadVideoPlay::PutVideoFrame(EyerAVFrame * videoFrame)
    {
        videoFrameQueue.PushLock(videoFrame);
        return 0;
    }

    EyerAVFrame * ThreadVideoPlay::GetVideoFrame()
    {
        EyerAVFrame * videoFrame = nullptr;
        videoFrameQueue.Lock();
        if(videoFrameQueue.Size() > 0){
            videoFrame = videoFrameQueue.FrontPop();
        }
        videoFrameQueue.Unlock();
        return videoFrame;
    }
}