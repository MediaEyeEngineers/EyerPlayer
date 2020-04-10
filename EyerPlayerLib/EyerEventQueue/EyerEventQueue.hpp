//
// Created by redknot on 2020/3/26.
//

#ifndef EYE_LIB_EYEREVENTQUEUE_HPP
#define EYE_LIB_EYEREVENTQUEUE_HPP

#include "EyerCore/EyerCore.hpp"

#include <queue>
#include <mutex>

namespace Eyer
{
    class EyerEventQueue;
    class EyerEvent;

    class EyerEventQueue
    {
    public:
        EyerEventQueue();
        ~EyerEventQueue();

        int Push(EyerEvent * event);
        int Pop();

        int Front(EyerEvent * & event);

        int FrontTarget(EyerEvent * & event, const EyerString & target);
        int FrontTargetAndPop(EyerEvent * & event, const EyerString & target);

        long long GetEventId();
    private:
        std::queue<EyerEvent *> eventQueue;
        std::mutex mutex;

        long long idIndex = 0;
    };


    class EyerEvent
    {
    public:
        EyerEvent();
        virtual ~EyerEvent();

        EyerEvent(EyerEvent & event);

        EyerEvent & operator = (const EyerEvent & event);

        virtual int GetType() = 0;

        EyerString GetFrom();
        EyerString GetTo();

        int SetFrom(const EyerString & from);
        int SetTo(const EyerString & to);

        int SetId(long long id);
        long long GetId();

        int SetRequestId(long long id);
        long long GetRequestId();
    private:
        EyerString from;
        EyerString to;

        long long id = 0;
        long long requestId = 0;
    };
}

#endif //EYE_LIB_EYEREVENTQUEUE_HPP
