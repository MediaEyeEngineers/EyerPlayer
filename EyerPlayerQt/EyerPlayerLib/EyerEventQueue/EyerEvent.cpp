//
// Created by redknot on 2020/3/26.
//

#include "EyerEventQueue.hpp"

namespace Eyer
{
    EyerEvent::EyerEvent()
    {

    }

    EyerEvent::~EyerEvent()
    {

    }

    EyerEvent::EyerEvent(EyerEvent & event)
    {
        *this = event;
    }

    EyerEvent & EyerEvent::operator = (const EyerEvent & event)
    {
        from = event.from;
        to = event.to;
        id = event.id;

        return *this;
    }

    EyerString EyerEvent::GetFrom()
    {
        return from;
    }

    EyerString EyerEvent::GetTo()
    {
        return to;
    }

    int EyerEvent::SetFrom(const EyerString & _from)
    {
        from = _from;
        return 0;
    }

    int EyerEvent::SetTo(const EyerString & _to)
    {
        to = _to;
        return 0;
    }

    int EyerEvent::SetId(long long _id)
    {
        id = _id;
        return  0;
    }

    long long EyerEvent::GetId()
    {
        return id;
    }

    int EyerEvent::SetRequestId(long long id)
    {
        requestId = id;
        return 0;
    }
    long long EyerEvent::GetRequestId()
    {
        return requestId;
    }
}