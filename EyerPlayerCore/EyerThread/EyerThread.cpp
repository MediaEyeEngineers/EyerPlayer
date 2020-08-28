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
        eventMut.lock();

        std::unique_lock<std::mutex> lck(eventLoopMut);

        eventLoopIsEndFlag = 0;

        eventLoopIsStartFlag = 0;

        // 发出 开始指令
        eventLoopFlag = 1;

        // 等待 开始
        while(eventLoopIsStartFlag == 0){
            eventLoopIsStart.wait(lck);
        }

        return 0;
    }

    int EyerThread::StopEventLoop()
    {
        std::unique_lock<std::mutex> lck(eventLoopMut);

        // 发出 停止指令
        eventLoopFlag = 0;

        // 等待 停止
        while(eventLoopIsEndFlag == 0){
            eventLoopIsEnd.wait(lck);
        }

        eventMut.unlock();
        return 0;
    }

    int EyerThread::EventLoop()
    {
        if(!eventLoopFlag){
            return -1;
        }

        // eventLoopIsStartFlag = 1;
        // eventLoopIsStart.notify_all();

        while(eventQueue.size() > 0){
            EyerRunnable * event = eventQueue.front();
            eventQueue.pop();
            event->Run();
        }

        while(eventLoopFlag){
            eventLoopIsStartFlag = 1;
            eventLoopIsStart.notify_all();
            Eyer::EyerTime::EyerSleepMilliseconds(1);
        }

        eventLoopIsEndFlag = 1;
        eventLoopIsEnd.notify_all();

        return 0;
    }
}