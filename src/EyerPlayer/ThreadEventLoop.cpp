#include "ThreadEventLoop.hpp"

namespace Eyer
{
    ThreadEventLoop::ThreadEventLoop()
    {
        eventQueue.AddObserver(this);
    }

    ThreadEventLoop::~ThreadEventLoop()
    {
        eventQueue.RemoveObserver(this);
    }

    int ThreadEventLoop::PushEvent(const EyerSmartPtr<Event> & event)
    {
        eventQueue.Push(event);
        return 0;
    }

    void ThreadEventLoop::Run()
    {
        EyerLog("ThreadEventLoop Start\n");

        std::mutex mu;

        while(1){
            if(stopFlag){
                break;
            }

            while(eventQueue.Size() > 0) {
                EyerSmartPtr<Event> event(nullptr);
                eventQueue.FrontPop(event);
                if (event != nullptr) {
                    if(event->type == EventType::PLAY_REQUEST){
                        EyerLog("PLAY_REQUEST\n");
                    }
                    else {
                        EyerLog("UNKNOW\n");
                    }
                }
            }

            std::unique_lock<std::mutex> locker(mu);
            cv.wait(locker);
        }

        EyerLog("ThreadEventLoop End\n");
    }

    int ThreadEventLoop::Update()
    {
        cv.notify_one();
        return 0;
    }
}