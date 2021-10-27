#include "ThreadPlayCtr.hpp"

#include "EyerCore/EyerCore.hpp"
#include "ThreadEventLoop.hpp"
#include "EyerDecodeQueue/EyerDecodeQueueHeader.hpp"

namespace Eyer
{
    ThreadPlayCtr::ThreadPlayCtr(QueueBox * _queueBox, ThreadEventLoop * _eventLoop)
        : eventLoop(_eventLoop)
        , queueBox(_queueBox)
    {

    }

    ThreadPlayCtr::~ThreadPlayCtr()
    {

    }

    void ThreadPlayCtr::Run()
    {
        EyerLog("ThreadPlayCtr Start\n");

        int videoStreamIndex = 0;
        int audioStreamIndex = 1;
        EyerAVFrame * videoFrame = nullptr;
        EyerAVFrame * audioFrame = nullptr;

        // 该线程用于控制视频流
        while(!stopFlag) {
            std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
            while(!stopFlag) {
                if(queueBox->IsStart()){
                    // 开始后才对 Frame 队列进行判断
                    if(status == PLAY_CTR_STATUS::PLAYING){
                        break;
                    }
                    else if(status == PLAY_CTR_STATUS::PAUSEING){
                        if(eventLoopFlag){
                            break;
                        }
                    }
                }
                queueBox->cvBox.cv.wait(locker);
            }

            locker.unlock();
            EventLoop();
            locker.lock();

            if(status != PLAY_CTR_STATUS::PLAYING){
                continue;
            }

            if(!queueBox->IsStart()){
                continue;
            }

            locker.unlock();

            // 获取到时间
            if(startTime <= 0){
                startTime = Eyer::EyerTime::GetTime();
            }
            long long nowTime = Eyer::EyerTime::GetTime();
            dTime = (nowTime - startTime) / 1000.0;
            dTime += pausedTime;

            if(videoFrame == nullptr){
                locker.lock();
                videoFrame = GetFrameFromDecodeQueue(videoStreamIndex);
                if(videoFrame != nullptr){
                    queueBox->cvBox.cv.notify_all();
                }
                locker.unlock();
            }
            if(audioFrame == nullptr){
                locker.lock();
                audioFrame = GetFrameFromDecodeQueue(audioStreamIndex);
                if(audioFrame != nullptr){
                    queueBox->cvBox.cv.notify_all();
                }
                locker.unlock();
            }

            // 判断播放
            // EyerLog("dTime: %f\n", dTime);
            if(videoFrame != nullptr){
                double playTime = videoFrame->GetSecPTS();
                if(dTime >= playTime){
                    EyerLog("Video PlayTime: %f\n", playTime);
                    locker.lock();
                    EyerObserverQueue<EyerAVFrame *> * outputQueue = queueBox->GetVideoOutputQueue();
                    outputQueue->Lock();
                    outputQueue->Push(videoFrame);
                    while(outputQueue->Size() >= 5){
                        EyerAVFrame * f = outputQueue->FrontPop();
                        if(f != nullptr){
                            delete f;
                        }
                    }
                    outputQueue->Unlock();
                    queueBox->cvBox.cv.notify_all();
                    locker.unlock();

                    videoFrame = nullptr;
                }
            }
            if(audioFrame != nullptr){
                double playTime = audioFrame->GetSecPTS();
                if(dTime >= playTime){
                    // EyerLog("Audio PlayTime: %f\n", playTime);
                    locker.lock();
                    EyerObserverQueue<EyerAVFrame *> * outputQueue = queueBox->GetAudioOutputQueue();
                    outputQueue->Lock();
                    outputQueue->Push(audioFrame);
                    while(outputQueue->Size() >= 5){
                        EyerAVFrame * f = outputQueue->FrontPop();
                        if(f != nullptr){
                            delete f;
                        }
                    }
                    outputQueue->Unlock();
                    queueBox->cvBox.cv.notify_all();
                    locker.unlock();

                    audioFrame = nullptr;
                }
            }

            if(videoFrame == nullptr || audioFrame == nullptr) {
                continue;
            }
            else {
                double sleepTimeA = std::abs(videoFrame->GetSecPTS() - dTime);
                double sleepTimeB = std::abs(audioFrame->GetSecPTS() - dTime);
                long long sleepTime = std::min(sleepTimeA, sleepTimeB) * 1000;
                EyerTime::EyerSleepMilliseconds(sleepTime);
            }
        }
        EyerLog("ThreadPlayCtr End\n");
    }

    EyerAVFrame * ThreadPlayCtr::GetFrameFromDecodeQueue(int streamId)
    {
        EyerAVFrame * frame = nullptr;

        EyerDeocdeQueue * decodeQueue = queueBox->GetDeocdeQueue(streamId);
        decodeQueue->FrameQueueLock();
        int size = decodeQueue->FrameQueueGetSize();
        if(size > 0){
            frame = decodeQueue->FrameQueueFrontPop();
        }
        decodeQueue->FrameQueueUnlock();

        return frame;
    }

    int ThreadPlayCtr::Pause()
    {
        EyerLog("ThreadPlayCtr Pause\n");
        std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
        pausedTime = dTime;
        status = PLAY_CTR_STATUS::PAUSEING;
        queueBox->cvBox.cv.notify_all();
        return 0;
    }

    int ThreadPlayCtr::Resume()
    {
        EyerLog("ThreadPlayCtr Resume\n");
        std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
        startTime = Eyer::EyerTime::GetTime();
        status = PLAY_CTR_STATUS::PLAYING;
        queueBox->cvBox.cv.notify_all();
        return 0;
    }

    int ThreadPlayCtr::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
        stopFlag = 1;
        queueBox->cvBox.cv.notify_all();
        return 0;
    }

    int ThreadPlayCtr::SetStartEventLoopFlag()
    {
        std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
        eventLoopFlag = 1;
        queueBox->cvBox.cv.notify_all();
        return 0;
    }
}