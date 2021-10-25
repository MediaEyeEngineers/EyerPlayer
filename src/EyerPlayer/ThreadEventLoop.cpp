#include "ThreadEventLoop.hpp"

namespace Eyer
{
    ThreadEventLoop::ThreadEventLoop()
    {
    }

    ThreadEventLoop::~ThreadEventLoop()
    {
        eventQueue.Lock();
        while(eventQueue.Size() > 0){
            Event * event = eventQueue.FrontPop();
            delete event;
        }
        eventQueue.Unlock();
    }

    int ThreadEventLoop::PushEvent(Event * event)
    {
        std::unique_lock<std::mutex> locker(mtx);
        eventQueue.Push(event);
        cv.notify_all();
        return 0;
    }

    void ThreadEventLoop::Run()
    {
        EyerLog("ThreadEventLoop Start\n");
        while(!stopFlag){
            std::unique_lock<std::mutex> locker(mtx);
            while(!stopFlag && eventQueue.SizeLock() <= 0) {
                cv.wait(locker);
            }

            eventQueue.Lock();
            while(eventQueue.Size() > 0) {
                Event * event = eventQueue.FrontPop();
                if (event != nullptr) {
                    ProcessEvent(event);
                }
                if(event != nullptr){
                    delete event;
                    event = nullptr;
                }
            }
            eventQueue.Unlock();
        }

        eventQueue.Lock();
        while(eventQueue.Size() > 0){
            Event * event = eventQueue.FrontPop();
            delete event;
        }
        eventQueue.Unlock();
        EyerLog("ThreadEventLoop End\n");
    }

    int ThreadEventLoop::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(mtx);
        stopFlag = 1;
        cv.notify_all();
        return 0;
    }

    int ThreadEventLoop::ProcessEvent(Event * event)
    {
        if(event->type == EventType::PLAY_REQUEST){
            EventRequest_Play * playEvent = (EventRequest_Play *)event;
            EyerLog("PLAY_REQUEST\n");
            if(readerThread != nullptr){
                // 报错，请别瞎比启动
            }
            readerThread = new ThreadReader(playEvent->url, &queueBox, this);
            readerThread->Start();
        }
        else if(event->type == EventType::PAUSE_REQUEST){
            EyerLog("PAUSE_REQUEST\n");
        }
        else if(event->type == EventType::STOP_REQUEST){
            EyerLog("STOP_REQUEST\n");
            if(readerThread == nullptr){
                // 还没开始
            }
            if(readerThread != nullptr){
                readerThread->Stop();
                delete readerThread;
                readerThread = nullptr;
            }
        }
        else {
            EyerLog("UNKNOW\n");
        }

        return 0;
    }

    QueueBox * ThreadEventLoop::GetQueueBox()
    {
        return &queueBox;
    }
}