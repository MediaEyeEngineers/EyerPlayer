#include "ThreadEventLoop.hpp"

namespace Eyer
{
    ThreadEventLoop::ThreadEventLoop()
    {
    }

    ThreadEventLoop::~ThreadEventLoop()
    {
    }

    int ThreadEventLoop::PushEvent(const EyerSmartPtr<Event> & event)
    {
        eventQueue.Push(event);
        return 0;
    }

    void ThreadEventLoop::Run()
    {
        EyerLog("ThreadEventLoop Start\n");
        while(!stopFlag){
            std::unique_lock<std::mutex> locker(mtx);
            while(!stopFlag && eventQueue.Size() <= 0) {
                cv.wait(locker);
            }

            while(eventQueue.Size() > 0) {
                EyerSmartPtr<Event> event(nullptr);
                eventQueue.FrontPop(event);
                if (event != nullptr) {
                    ProcessEvent(event);
                }
            }
        }
        EyerLog("ThreadEventLoop End\n");
    }

    int ThreadEventLoop::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(mtx);
        stopFlag = 1;
        cv.notify_all();
        return 0;
    }

    int ThreadEventLoop::ProcessEvent(const EyerSmartPtr<Event> & event)
    {
        if(event->type == EventType::PLAY_REQUEST){
            EyerLog("PLAY_REQUEST\n");
            if(readerThread != nullptr){
                // 报错，请别瞎比启动
            }
            readerThread = new ThreadReader(&queueBox, this);
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
}