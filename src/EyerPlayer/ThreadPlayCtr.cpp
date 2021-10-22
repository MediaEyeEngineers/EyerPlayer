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

            if(startTime <= 0){
                startTime = Eyer::EyerTime::GetTime();
            }

            long long nowTime = Eyer::EyerTime::GetTime();

            long long dTime = nowTime - startTime;
            for(int i=0;i<2;i++){
                EyerAVFrame * frame = nullptr;

                locker.lock();
                frame = GetFrameFromDecodeQueue(i);
                if(frame != nullptr){
                    queueBox->cvBox.cv.notify_all();
                }
                locker.unlock();

                if(frame != nullptr){
                    EyerLog("Frame PTS: %f\n", frame->GetSecPTS());
                    EyerLog("D Time: %f\n", dTime / 1000.0);
                    delete frame;
                    frame = nullptr;
                }
            }
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
}