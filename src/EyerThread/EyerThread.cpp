#include "EyerThread.hpp"

#include <functional>

#include <time.h>
#include <stdio.h>
#include <chrono>
#include <thread>

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
        if(onStopPromise != nullptr){
            delete onStopPromise;
            onStopPromise = nullptr;
        }
        if(onStopFinishPromise != nullptr){
            delete onStopFinishPromise;
            onStopFinishPromise = nullptr;
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

            // 等待结束的命令
            onStopPromise->get_future().get();

            eventLoopFlag = 0;

            if(onStopFinishPromise != nullptr){
                onStopFinishPromise->set_value();
            }
        }
        return 0;
    }

    int EyerThread::StartEventLoop()
    {
        onStartedPromise        = new std::promise<void>();
        onStopPromise           = new std::promise<void>();
        onStopFinishPromise     = new std::promise<void>();

        SetStartEventLoopFlag();
        // 等待运行开始后的信号
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
        if(onStopPromise != nullptr){
            onStopPromise->set_value();
        }

        if(onStopFinishPromise != nullptr){
            // 等待重制状态
            onStopFinishPromise->get_future().get();
        }


        if(onStartedPromise != nullptr){
            delete onStartedPromise;
            onStartedPromise = nullptr;
        }
        if(onStopPromise != nullptr){
            delete onStopPromise;
            onStopPromise = nullptr;
        }
        if(onStopFinishPromise != nullptr){
            delete onStopFinishPromise;
            onStopFinishPromise = nullptr;
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