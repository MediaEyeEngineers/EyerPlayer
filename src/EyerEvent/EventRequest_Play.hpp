#ifndef EYERCAMERA_EVENTREQUEST_PLAY_HPP
#define EYERCAMERA_EVENTREQUEST_PLAY_HPP

#include "EventRequest.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EventRequest_Play : public EventRequest
    {
    public:
        EventRequest_Play();
        ~EventRequest_Play();

        EyerString url;
    };
}

#endif //EYERCAMERA_EVENTREQUEST_PLAY_HPP
