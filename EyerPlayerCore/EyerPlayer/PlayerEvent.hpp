#ifndef EYERPLAYERLIB_PLAYER_EVENT_H
#define EYERPLAYERLIB_PLAYER_EVENT_H

#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EventTag.hpp"
#include "EventType.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerPlayer.hpp"
#include "MediaInfo.hpp"

namespace Eyer {
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

        double progress = 0.0;
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















    class EventSetGLCtxRequest : public Eyer::EyerEvent
    {
    public:
        EventSetGLCtxRequest()
        {

        }

        ~EventSetGLCtxRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::SetGLCtxRequest;
        }

        Eyer::EyerGLContextThread * glCtx = nullptr;
    };


    class EventSetGLCtxResponse : public Eyer::EyerEvent
    {
    public:
        EventSetGLCtxResponse()
        {

        }

        ~EventSetGLCtxResponse()
        {

        }

        virtual int GetType()
        {
            return EventType::SetGLCtxResponse;
        }
    };









    class EventUnbindGLCtxRequest : public Eyer::EyerEvent
    {
    public:
        EventUnbindGLCtxRequest()
        {

        }

        ~EventUnbindGLCtxRequest()
        {

        }

        virtual int GetType()
        {
            return EventType::UnbindGLCtxRequest;
        }
    };


    class EventUnbindGLCtxResponse : public Eyer::EyerEvent
    {
    public:
        EventUnbindGLCtxResponse()
        {

        }

        ~EventUnbindGLCtxResponse()
        {

        }

        virtual int GetType()
        {
            return EventType::UnbindGLCtxResponse;
        }
    };





    class DemoRunnable: public EyerRunnable
    {
    public:
        virtual void Run()
        {
            EyerLog("DemoRunnable\n");
        }
    };




    class SEEK_Reader_Runnable: public EyerRunnable
    {
    public:
        SEEK_Reader_Runnable(AVReaderThread * _readerThread, double _seekTime)
        {
            readerThread = _readerThread;
            seekTime = _seekTime;
        }

        virtual void Run()
        {
            EyerLog("SEEK_Reader_Runnable, SeekTime: %f\n", seekTime);

            readerThread->Seek(seekTime);
        }

    private:
        AVReaderThread * readerThread = nullptr;
        double seekTime = 0.0;
    };



    class SEEK_Decoder_Runnable: public EyerRunnable
    {
    public:
        SEEK_Decoder_Runnable(AVDecoderThread * _decoderThread)
        {
            decoderThread = _decoderThread;
        }

        virtual void Run()
        {
            EyerLog("SEEK_Decoder_Runnable\n");
            decoderThread->FlushDecoder();
            decoderThread->ClearAllPacket();
        }

    private:
        AVDecoderThread * decoderThread = nullptr;
    };

    class SEEK_PlayCtr_Runnable: public EyerRunnable
    {
    public:
        SEEK_PlayCtr_Runnable(AVPlayCtrThread * _playCtr, double _time)
        {
            playCtr = _playCtr;
            time = _time;
        }

        virtual void Run()
        {
            EyerLog("SEEK_PlayCtr_Runnable\n");
            playCtr->Seek(time);
        }

    private:
        AVPlayCtrThread * playCtr = nullptr;
        double time = 0.0;
    };
}

#endif // EYERPLAYERLIB_PLAYER_EVENT_H
