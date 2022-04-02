#include "EventType.hpp"

namespace Eyer
{
    EventType EventType::UNKNOW         (0, "UNKNOW");
    EventType EventType::PLAY_REQUEST   (1, "PLAY_REQUEST");
    EventType EventType::STOP_REQUEST   (2, "STOP_REQUEST");
    EventType EventType::PAUSE_REQUEST  (3, "PAUSE_REQUEST");
    EventType EventType::RESUME_REQUEST (4, "RESUME_REQUEST");
    EventType EventType::SEEK_REQUEST   (5, "SEEK_REQUEST");

    EventType::EventType()
    {

    }

    EventType::EventType(int _id, const EyerString & _typeStr)
    {
        id = _id;
        typeStr = _typeStr;
    }

    EventType::EventType(const EventType & eventType)
    {
        *this = eventType;
    }

    EventType::~EventType()
    {

    }

    EventType & EventType::operator = (const EventType & eventType)
    {
        id = eventType.id;
        typeStr = eventType.typeStr;
        return *this;
    }

    bool EventType::operator == (const EventType & eventType)
    {
        return id == eventType.id;
    }

    bool EventType::operator != (const EventType & eventType)
    {
        return id != eventType.id;
    }
}