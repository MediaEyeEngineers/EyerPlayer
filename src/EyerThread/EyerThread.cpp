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

        if(startPromise != nullptr){
            delete startPromise;
            startPromise = nullptr;
        }
        if(stopPromise != nullptr){
            delete stopPromise;
            stopPromise = nullptr;
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
            // printf("Start Event\n");
            // Doing Event
            for(int i=0;i<eventList.size();i++){
                eventList[i]->Run();
            }

            stopPromise = new std::promise<void>();

            if(startPromise != nullptr){
                startPromise->set_value();
            }
            // printf("End Event\n");

            stopPromise->get_future().get();

            if(stopPromise != nullptr){
                delete stopPromise;
                stopPromise = nullptr;
            }
            eventLoopFlag = 0;
        }
        return 0;
    }

    int EyerThread::StartEventLoop()
    {
        startPromise = new std::promise<void>();
        SetStartEventLoopFlag();
        // 等待运行结束后的信号
        startPromise->get_future().get();
        if(startPromise != nullptr){
            delete startPromise;
            startPromise = nullptr;
        }
        return 0;
    }

    int EyerThread::SetStartEventLoopFlag()
    {
        eventLoopFlag = 1;
        return 0;
    }

    int EyerThread::StopEventLoop()
    {
        if(stopPromise != nullptr){
            stopPromise->set_value();
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