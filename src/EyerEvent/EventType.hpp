#ifndef EYERCAMERA_EVENTTYPE_HPP
#define EYERCAMERA_EVENTTYPE_HPP

namespace Eyer
{
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

        UNKNOW
    };
}

#endif //EYERCAMERA_EVENTTYPE_HPP
