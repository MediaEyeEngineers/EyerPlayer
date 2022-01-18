#include "EyerThread.hpp"

#include <functional>

namespace Eyer
{
    EyerThread::EyerThread()
    {

    }

    EyerThread::~EyerThread()
    {
        Stop();

        if(onStartedPromise != nullptr){
            delete onStartedPromise;
            onStartedPromise = nullptr;
        }
        if(onEventFinishPromise != nullptr){
            delete onEventFinishPromise;
            onEventFinishPromise = nullptr;
        }
        if(onStopedPromise != nullptr){
            delete onStopedPromise;
            onStopedPromise = nullptr;
        }
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

        SetStopFlag();

        if(t != nullptr){
            t->join();
            delete t;
            t = nullptr;
        }
        stopFlag = 0;

        return 0;
    }

    int EyerThread::SetStopFlag()
    {
        stopFlag = 1;
        return 0;
    }


    int EyerThread::EventLoop()
    {
        if(eventLoopFlag){
            if(onStartedPromise != nullptr){
                onStartedPromise->set_value();
            }

            // printf("Start Event\n");
            // Doing Event
            for(int i=0;i<eventList.size();i++){
                eventList[i]->Run();
            }

            if(onEventFinishPromise != nullptr){
                onEventFinishPromise->set_value();
            }

            onStopedPromise->get_future().get();

            eventLoopFlag = 0;
        }
        return 0;
    }

    int EyerThread::StartEventLoop()
    {
        onStartedPromise        = new std::promise<void>();
        onEventFinishPromise    = new std::promise<void>();
        onStopedPromise         = new std::promise<void>();

        SetStartEventLoopFlag();
        // 等待运行结束后的信号
        onStartedPromise->get_future().get();
        return 0;
    }

    int EyerThread::SetStartEventLoopFlag()
    {
        eventLoopFlag = 1;
        return 0;
    }

    int EyerThread::StopEventLoop()
    {
        onEventFinishPromise->get_future().get();

        if(onStopedPromise != nullptr){
            onStopedPromise->set_value();
        }

        if(onStartedPromise != nullptr){
            delete onStartedPromise;
            onStartedPromise = nullptr;
        }
        if(onEventFinishPromise != nullptr){
            delete onEventFinishPromise;
            onEventFinishPromise = nullptr;
        }
        if(onStopedPromise != nullptr){
            delete onStopedPromise;
            onStopedPromise = nullptr;
        }

        return 0;
    }

    int EyerThread::PushEvent(EyerRunnable * runnable)
    {
        eventList.push_back(runnable);
        return 0;
    }

    int EyerThread::ClearAllEvent()
    {
        eventList.clear();
        return 0;
    }
}