#ifndef EYERCAMERA_THREADEVENTLOOP_HPP
#define EYERCAMERA_THREADEVENTLOOP_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerEvent/EyerEventHeader.hpp"
#include "ThreadReader.hpp"
#include "ThreadPlayCtr.hpp"

namespace Eyer
{
    class ThreadEventLoop : public EyerThread, public EyerObserver
    {
    public:
        ThreadEventLoop();
        ~ThreadEventLoop();

        int PushEvent(const EyerSmartPtr<Event> & event);

        virtual void Run() override;

        virtual int Update() override;

    private:
        EyerObserverQueue<EyerSmartPtr<Event>> eventQueue;

        int ProcessEvent(const EyerSmartPtr<Event> & event);

        // 线程
        ThreadPlayCtr * playCtrThread = nullptr;
        ThreadReader * readerThread = nullptr;
    };
}



#endif //EYERCAMERA_THREADEVENTLOOP_HPP
