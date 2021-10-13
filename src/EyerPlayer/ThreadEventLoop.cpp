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

        std::unique_lock<std::mutex> locker(mut);

        while(1){
            if(stopFlag){
                break;
            }

            while(eventQueue.Size() > 0) {
                EyerSmartPtr<Event> event(nullptr);
                eventQueue.FrontPop(event);
                if (event != nullptr) {
                    ProcessEvent(event);
                }
            }

            // Eyer::EyerTime::EyerSleepMilliseconds(1);


            cv.wait(locker);
        }

        EyerLog("ThreadEventLoop End\n");
    }

    int ThreadEventLoop::Update()
    {
        Notify();
        return 0;
    }

    int ThreadEventLoop::ProcessEvent(const EyerSmartPtr<Event> & event)
    {
        if(event->type == EventType::PLAY_REQUEST){
            EyerLog("PLAY_REQUEST\n");
            if(readerThread != nullptr){
                // 报错，请先暂停
            }
            readerThread = new ThreadReader(this);
            readerThread->Start();

            playCtrThread = new ThreadPlayCtr(this);
            playCtrThread->Start();
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
            if(playCtrThread != nullptr){
                playCtrThread->Stop();
                delete playCtrThread;
                playCtrThread = nullptr;
            }
        }
        else {
            EyerLog("UNKNOW\n");
        }

        return 0;
    }
}