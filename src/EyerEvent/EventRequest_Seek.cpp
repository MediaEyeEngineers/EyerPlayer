#include "EventRequest_Seek.hpp"

namespace Eyer
{
    EventRequest_Seek::EventRequest_Seek()
    {
        type = EventType::SEEK_REQUEST;
    }

    EventRequest_Seek::~EventRequest_Seek()
    {

    }
}