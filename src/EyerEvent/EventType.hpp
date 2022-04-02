#ifndef EYERCAMERA_EVENTTYPE_HPP
#define EYERCAMERA_EVENTTYPE_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EventType
    {
    public:
        static EventType UNKNOW;
        static EventType PLAY_REQUEST;
        static EventType STOP_REQUEST;
        static EventType PAUSE_REQUEST;
        static EventType RESUME_REQUEST;
        static EventType SEEK_REQUEST;
    public:
        EventType();
        EventType(int _id, const EyerString & _typeStr);
        EventType(const EventType & eventType);
        ~EventType();

        EventType & operator = (const EventType & eventType);

        bool operator == (const EventType & eventType);
        bool operator != (const EventType & eventType);

    public:
        int id = 0;
        EyerString typeStr;
    };

    /*
    enum class EventType
    {
        PLAY_REQUEST,
        PLAY_RESPONSE,

        PAUSE_REQUEST,
        PAUSE_RESPONSE,

        RESUME_REQUEST,
        RESUME_RESPONSE,

        STOP_REQUEST,
        STOP_RESPONSE,

        SEEK_REQUEST,
        SEEK_RESPONSE,

        UNKNOW
    };
    */
}

#endif //EYERCAMERA_EVENTTYPE_HPP
