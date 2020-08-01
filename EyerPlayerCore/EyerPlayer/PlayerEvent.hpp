#ifndef EYERPLAYERLIB_PLAYER_EVENT_H
#define EYERPLAYERLIB_PLAYER_EVENT_H

#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EventTag.hpp"
#include "EventType.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerPlayer.hpp"
#include "MediaInfo.hpp"

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









    class EventPlayRequest : public Eyer::EyerEvent
    {
    public:
        EventPlayRequest()
        {

        }

        ~EventPlayRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::PLAYRequest;
        }
    };
    class EventPauseRequest : public Eyer::EyerEvent
    {
    public:
        EventPauseRequest()
        {

        }

        ~EventPauseRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::PAUSERequest;
        }
    };








    class EventProgressRequest : public Eyer::EyerEvent
    {
    public:
        EventProgressRequest()
        {

        }

        ~EventProgressRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::PROGRESSRequest;
        }

        double playTime = 0.0f;
    };





    class EventSeekRequest : public Eyer::EyerEvent
    {
    public:
        EventSeekRequest()
        {

        }

        ~EventSeekRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::SEEKRequest;
        }

        double time = 0.0f;
    };



    class EventLagStartRequest : public Eyer::EyerEvent
    {
    public:
        EventLagStartRequest()
        {

        }

        ~EventLagStartRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::LAGStartRequest;
        }
    };


    class EventLagStopRequest : public Eyer::EyerEvent
    {
    public:
        EventLagStopRequest()
        {

        }

        ~EventLagStopRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::LAGStopRequest;
        }
    };
}

#endif // EYERPLAYERLIB_PLAYER_EVENT_H
