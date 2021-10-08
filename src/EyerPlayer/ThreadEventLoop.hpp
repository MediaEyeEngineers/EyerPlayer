#ifndef EYERCAMERA_THREADEVENTLOOP_HPP
#define EYERCAMERA_THREADEVENTLOOP_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerCore/EyerCore.hpp"
#include "Event.hpp"

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
    };
}



#endif //EYERCAMERA_THREADEVENTLOOP_HPP
