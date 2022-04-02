#include "EventControlThread.hpp"

#include "EyerEvent/EyerEventHeader.hpp"

namespace Eyer
{
    EventControlThread::EventControlThread()
    {

    }

    EventControlThread::~EventControlThread()
    {
        eventQueue.Lock();
        while(eventQueue.Size() > 0){
            EyerPlayerEvent * event = eventQueue.FrontPop();
            if(event != nullptr){
                delete event;
                event = nullptr;
            }
        }
        eventQueue.Unlock();
    }

    int EventControlThread::PushEvent(EyerPlayerEvent * event)
    {
        std::unique_lock<std::mutex> locker(mtx);
        eventQueue.Push(event);
        cv.notify_all();
        return 0;
    }

    void EventControlThread::Run()
    {
        EyerLog("ThreadEventLoop Start\n");
        std::unique_lock<std::mutex> locker(mtx);
        while(1){
            cv.wait_for(locker, std::chrono::milliseconds(1000));
            if(stopFlag){
                break;
            }
            if(eventQueue.SizeLock() <= 0){
                continue;
            }

            eventQueue.Lock();
            while (eventQueue.Size() > 0){
                EyerPlayerEvent * event = eventQueue.FrontPop();
                ProcessEvent(event);
                if(event != nullptr){
                    delete event;
                    event = nullptr;
                }
            }
            eventQueue.Unlock();
        }

        // 结束之前再来一次
        eventQueue.Lock();
        while (eventQueue.Size() > 0){
            EyerPlayerEvent * event = eventQueue.FrontPop();
            ProcessEvent(event);
            if(event != nullptr){
                delete event;
                event = nullptr;
            }
        }
        eventQueue.Unlock();

        EyerLog("ThreadEventLoop End\n");
    }

    int EventControlThread::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(mtx);
        stopFlag = 1;
        cv.notify_all();
        return 0;
    }

    int EventControlThread::ProcessEvent(EyerPlayerEvent * event)
    {
        if(event == nullptr){
            return -1;
        }

        EyerLog("Loop, %s\n", event->type.typeStr.c_str());

        if(event->type == EventType::PLAY_REQUEST){
            if(ioReadThread != nullptr){
                // 报错
                return -1;
            }
            EyerPlayerEvent_Play * eventRequestPlay = (EyerPlayerEvent_Play *)event;
            playerContext.url = eventRequestPlay->url;
            ioReadThread = new IOReadThread(&playerContext);
            ioReadThread->Start();
        }
        else if(event->type == EventType::STOP_REQUEST){
            if(ioReadThread == nullptr){
                // 报错
                return -1;
            }
            if(ioReadThread != nullptr){
                ioReadThread->Stop();
                delete ioReadThread;
                ioReadThread = nullptr;
            }
        }

        return 0;
    }
}