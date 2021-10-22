#include "ThreadPlayCtr.hpp"

#include "EyerCore/EyerCore.hpp"
#include "ThreadEventLoop.hpp"

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
        int videoStreamId = 0;
        int audioStreamId = 1;

        EyerLog("ThreadPlayCtr Start\n");

        long long startTime = -1;

        // 该线程用于控制视频流
        while(!stopFlag) {
            std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
            while(!stopFlag) {
                if(queueBox->IsStart()){
                    // 开始后才对 Frame 队列进行判断
                    break;
                }
                queueBox->cvBox.cv.wait(locker);
            }

            if(!queueBox->IsStart()){
                continue;
            }

            locker.unlock();

            EyerDeocdeQueue * videoDecodeQueue = queueBox->GetDeocdeQueue(videoStreamId);
            EyerDeocdeQueue * audioDecodeQueue = queueBox->GetDeocdeQueue(audioStreamId);

            if(startTime <= 0){
                startTime = Eyer::EyerTime::GetTime();
            }

            long long nowTime = Eyer::EyerTime::GetTime();

            long long dTime = nowTime - startTime;
            EyerLog("D Time: %lld\n", dTime);
            {
                /*
                videoDecodeQueue->FrameQueueLock();
                EyerLog("A\n");
                int size = videoDecodeQueue->FrameQueueGetSize();
                EyerLog("B: %d\n", size);
                if(size > 0){
                    EyerLog("BC\n");
                    locker.lock();
                    EyerLog("C\n");
                    EyerAVFrame * frame = videoDecodeQueue->FrameQueueFrontPop();
                    EyerLog("D\n");
                    queueBox->cvBox.cv.notify_all();
                    locker.unlock();

                    if(frame != nullptr){
                        EyerLog("%f\n", frame->GetSecPTS());
                        delete frame;
                        frame = nullptr;
                    }
                }
                videoDecodeQueue->FrameQueueUnlock();
                */
            }
            /*
            {
                audioDecodeQueue->FrameQueueLock();
                int size = audioDecodeQueue->FrameQueueGetSize();
                if(size > 0){
                    std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
                    EyerAVFrame * frame = audioDecodeQueue->FrameQueueFrontPop();
                    queueBox->cvBox.cv.notify_all();
                    if(frame != nullptr){
                        delete frame;
                        frame = nullptr;
                    }
                }
                audioDecodeQueue->FrameQueueUnlock();
            }
            */

            Eyer::EyerTime::EyerSleepMilliseconds(10);
        }
        EyerLog("ThreadPlayCtr End\n");
    }

    int ThreadPlayCtr::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(queueBox->cvBox.mtx);
        stopFlag = 1;
        queueBox->cvBox.cv.notify_all();
        return 0;
    }
}