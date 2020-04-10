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

    }

    int EyerThread::Stop(int t)
    {
        stopFlag = 1;
        while(1){
            if(!IsRunning()){
                break;
            }
            EyerTime::EyerSleep(t);
        }
        stopFlag = 0;
        return 0;
    }

    int EyerThread::WaitForStop(int t)
    {
        while(1){
            if(!IsRunning()){
                break;
            }
            EyerTime::EyerSleep(t);
        }
        return 0;
    }

    int EyerThread::IsRunning()
    {
        return isRun;
    }

    void EyerThread::Detach()
    {
        std::thread t(std::bind(&EyerThread::Run, this));
        t.detach();
    }

    void EyerThread::Join()
    {
        std::thread t(std::bind(&EyerThread::Run, this));
        t.join();
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