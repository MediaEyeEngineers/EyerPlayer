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
        isEventLooping = 1;
        return 0;
    }

    int EyerThread::StopEventLoop()
    {
        if(isEventLooping == 0){
            return -1;
        }

        for(;;){
            Eyer::EyerTime::EyerSleepMilliseconds(1);
            if(eventQueue.size() <= 0){
                break;
            }
        }

        isEventLooping = 0;

        return 0;
    }

    int EyerThread::EventLoop()
    {
        if(!isEventLooping){
            return -1;
        }


        while(eventQueue.size() > 0){
            EyerRunnable * event = eventQueue.front();
            eventQueue.pop();

            event->Run();
        }

        while(isEventLooping){
            Eyer::EyerTime::EyerSleepMilliseconds(1);
        }

        return 0;
    }
}