#include "EyerThread.hpp"

#include <functional>

namespace Eyer
{
    EyerThread::EyerThread()
    {

    }

    EyerThread::~EyerThread()
    {
        if(eventLoopPromise != nullptr){
            delete eventLoopPromise;
            eventLoopPromise = nullptr;
        }

        Stop();
    }

    int EyerThread::Start()
    {
        if(t != nullptr){
            return -1;
        }

        stopFlag = 0;
        t = new std::thread(&EyerThread::Run, this);

        return 0;
    }

    int EyerThread::Stop()
    {
        if(t == nullptr){
            return -1;
        }

        stopFlag = 1;
        Notify();
        if(t != nullptr){
            t->join();
            delete t;
            t = nullptr;
        }
        stopFlag = 0;

        return 0;
    }


    int EyerThread::EventLoop()
    {
        if(!eventLoopFlag){
            return 0;
        }

        while(eventLoopFlag){
            for(int i=0;i<eventQueue.size();i++){
                if(!eventQueue[i]->isOK){
                    eventQueue[i]->Run();
                    eventQueue[i]->isOK = true;
                    eventQueue[i]->promise.set_value();
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        eventQueue.clear();

        eventLoopPromise->set_value();

        return 0;
    }

    int EyerThread::StartEventLoop()
    {
        if(eventLoopPromise != nullptr){
            delete eventLoopPromise;
            eventLoopPromise = nullptr;
        }
        eventLoopPromise = new std::promise<void>();

        eventLoopFlag = true;

        Notify();

        for(int i=0;i<eventQueue.size();i++){
            eventQueue[i]->promise.get_future().get();
        }

        return 0;
    }

    int EyerThread::StopEventLoop()
    {
        eventLoopFlag = false;

        if(eventLoopPromise != nullptr){
            eventLoopPromise->get_future().get();

            delete eventLoopPromise;
            eventLoopPromise = nullptr;
        }

        return 0;
    }

    int EyerThread::PushEvent(EyerRunnable * runnable)
    {
        eventQueue.push_back(runnable);
        return 0;
    }

    int EyerThread::Notify()
    {
        cv.notify_all();
        return 0;
    }
}