#include "EventControlThread.hpp"

namespace Eyer
{
    EventControlThread::EventControlThread()
    {

    }

    EventControlThread::~EventControlThread()
    {
        eventQueue.Lock();
        while(eventQueue.Size() > 0){
            Event * event = eventQueue.FrontPop();
            if(event != nullptr){
                delete event;
                event = nullptr;
            }
        }
        eventQueue.Unlock();
    }

    int EventControlThread::PushEvent(Event * event)
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
            cv.wait_for(locker, std::chrono::milliseconds(100));
            if(stopFlag){
                break;
            }
            if(eventQueue.SizeLock() <= 0){
                continue;
            }

            eventQueue.Lock();
            if(eventQueue.Size() > 0){
                Event * event = eventQueue.FrontPop();
                ProcessEvent(event);
                if(event != nullptr){
                    delete event;
                    event = nullptr;
                }
            }
            eventQueue.Unlock();
        }
        EyerLog("ThreadEventLoop End\n");
    }

    int EventControlThread::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(mtx);
        stopFlag = 1;
        cv.notify_all();
        return 0;
    }

    int EventControlThread::ProcessEvent(Event * event)
    {
        if(event == nullptr){
            return -1;
        }

        EyerLog("Loop, %s\n", event->type.typeStr.c_str());
        if(event->type == EventType::PLAY_REQUEST){
            if(threadReader != nullptr){
                // 报错
                return -1;
            }
            EventRequest_Play * eventRequestPlay = (EventRequest_Play *)event;
            playerContext.url = eventRequestPlay->url;
            threadReader = new ThreadReader(&playerContext);
            threadReader->Start();
        }
        else if(event->type == EventType::STOP_REQUEST){
            if(threadReader == nullptr){
                // 报错
                return -1;
            }
            if(threadReader != nullptr){
                threadReader->Stop();
                delete threadReader;
                threadReader = nullptr;
            }
        }

        return 0;
    }
}