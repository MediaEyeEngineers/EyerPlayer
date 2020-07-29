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
}