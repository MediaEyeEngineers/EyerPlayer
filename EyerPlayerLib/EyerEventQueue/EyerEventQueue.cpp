//
// Created by redknot on 2020/3/26.
//

#include "EyerEventQueue.hpp"

namespace Eyer
{
    EyerEventQueue::EyerEventQueue()
    {

    }

    EyerEventQueue::~EyerEventQueue()
    {

    }

    int EyerEventQueue::FrontTargetAndPop(EyerEvent * & event, const EyerString & target)
    {
        mutex.lock();
        if(eventQueue.size() > 0) {
            EyerEvent * e = eventQueue.front();
            if(e == nullptr){
                mutex.unlock();
                return -1;
            }
            if(e->GetTo() == target){
                event = e;
                eventQueue.pop();
                mutex.unlock();
                return 0;
            }
        }
        mutex.unlock();
        return -1;
    }

    int EyerEventQueue::FrontTarget(EyerEvent * & event, const EyerString & target)
    {
        mutex.lock();
        if(eventQueue.size() > 0) {
            EyerEvent * e = eventQueue.front();
            if(e == nullptr){
                mutex.unlock();
                return 0;
            }
            if(e->GetTo() == target){
                event = e;
                mutex.unlock();
                return 0;
            }
        }
        mutex.unlock();
        return -1;
    }

    int EyerEventQueue::Push(EyerEvent * event)
    {
        mutex.lock();
        eventQueue.push(event);
        mutex.unlock();

        return 0;
    }

    int EyerEventQueue::Pop()
    {
        mutex.lock();
        if(eventQueue.size() > 0){
            eventQueue.pop();
        }
        mutex.unlock();

        return 0;
    }

    int EyerEventQueue::Front(EyerEvent * & event)
    {
        mutex.lock();
        if(eventQueue.size() > 0){
            event = eventQueue.front();
        }
        mutex.unlock();

        return 0;
    }

    long long EyerEventQueue::GetEventId()
    {
        idIndex++;
        return idIndex;
    }
}