#include "EventRequest_Stop.hpp"

namespace Eyer
{
    EventRequest_Stop::EventRequest_Stop()
    {
        type = EventType::STOP_REQUEST;
    }

    EventRequest_Stop::~EventRequest_Stop()
    {

    }
}