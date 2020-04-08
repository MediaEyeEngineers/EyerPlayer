#ifndef EYERPLAYERLIB_PLAYER_EVENT_H
#define EYERPLAYERLIB_PLAYER_EVENT_H

#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerPlayerLib.h"
#include "EyerPlayerConstant.h"
#include "EyerAV/EyerAV.hpp"

namespace EyerPlayer {
    class EventOpenRequest : public Eyer::EyerEvent
    {
    public:
        EventOpenRequest()
        {

        }

        ~EventOpenRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::OPENRequest;
        }

        Eyer::EyerString url;
    };

    class EventOpenResponse : public Eyer::EyerEvent
    {
    public:
        EventOpenResponse()
        {

        }

        ~EventOpenResponse()
        {

        }

        virtual int GetType()
        {
            return EventType::OPENResponse;
        }

        EventOpenStatus status = EventOpenStatus::OPEN_STATUS_SUCCESS;
        MediaInfo mediaInfo;
    };


    class EventStopRequest : public Eyer::EyerEvent
    {
    public:
        EventStopRequest()
        {

        }

        ~EventStopRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::STOPRequest;
        }
    };

    class EventStopResponse : public Eyer::EyerEvent
    {
    public:
        EventStopResponse()
        {

        }

        ~EventStopResponse()
        {

        }

        virtual int GetType()
        {
            return EventType::STOPResponse;
        }

        EventStopStatus status = EventStopStatus::STOP_STATUS_SUCCESS;
    };

    class EventUpdateUIRequest : public Eyer::EyerEvent
    {
    public:
        EventUpdateUIRequest()
        {

        }

        ~EventUpdateUIRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::UPDATEUIRequest;
        }

        int streamId = -1;
        Eyer::EyerAVFrame * frame = nullptr;
    };

    class EventUpdateAudioRequest : public Eyer::EyerEvent
    {
    public:
        EventUpdateAudioRequest()
        {

        }

        ~EventUpdateAudioRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::UPDATEAUDIORequest;
        }

        Eyer::EyerAVFrame * frame = nullptr;
    };
}

#endif // EYERPLAYERLIB_PLAYER_EVENT_H
