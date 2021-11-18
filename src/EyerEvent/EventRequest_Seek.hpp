#ifndef EYERPLAYER_EVENTREQUEST_SEEK_HPP
#define EYERPLAYER_EVENTREQUEST_SEEK_HPP

#include "EventRequest.hpp"

namespace Eyer
{
    class EventRequest_Seek : public EventRequest
    {
    public:
        EventRequest_Seek();
        ~EventRequest_Seek();
    };
}

#endif //EYERPLAYER_EVENTREQUEST_SEEK_HPP
