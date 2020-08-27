#include "EyerThread.hpp"

#include <functional>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerThread::EyerThread()
    {

    }

    EyerThread::~EyerThread()
    {
        Stop();

        while(eventQueue.size() > 0){
            EyerRunnable * event = eventQueue.front();
            eventQueue.pop();
        }
    }

    int EyerThread::Stop(int time)
    {
        if(t == nullptr){
            return -1;
        }

        stopFlag = 1;
        if(t != nullptr){
            t->join();
            delete t;
            t = nullptr;
        }
        stopFlag = 0;

        SetStoping();

        return 0;
    }

    int EyerThread::IsRunning()
    {
        return isRun;
    }

    int EyerThread::Start()
    {
        if(t != nullptr){
            return -1;
        }

        SetRunning();
        stopFlag = 0;
        t = new std::thread(&EyerThread::Run, this);

        return 0;
    }

    void EyerThread::SetRunning()
    {
        stopFlag = 0;
        isRun = 1;
    }

    void EyerThread::SetStoping()
    {
        isRun = 0;
    }


    int EyerThread::PushEvent(EyerRunnable * event)
    {
        eventQueue.push(event);
        return 0;
    }


    int EyerThread::StartEventLoop()
    {
        // 发出 开始指令
        eventLoopStart = 0;
        eventLoopEnd = 0;

        stopEventLoopFlag = 0;

        // 等待 开始
        while(eventLoopStart == 0){
            Eyer::EyerTime::EyerSleepMilliseconds(1);
        }

        eventLoopStart = 0;

        return 0;
    }

    int EyerThread::StopEventLoop()
    {
        // 发出 停止指令
        stopEventLoopFlag = 1;

        // 等待 停止
        while(eventLoopEnd == 0){
            Eyer::EyerTime::EyerSleepMilliseconds(1);
        }

        eventLoopEnd = 0;

        return 0;
    }

    int EyerThread::EventLoop()
    {
        while(!stopEventLoopFlag){
            eventLoopEnd = 0;
            eventLoopStart = 1;

            while(eventQueue.size()){
                EyerRunnable * event = eventQueue.front();
                eventQueue.pop();
                event->Run();
            }
        }

        eventLoopEnd = 1;

        return 0;
    }
}