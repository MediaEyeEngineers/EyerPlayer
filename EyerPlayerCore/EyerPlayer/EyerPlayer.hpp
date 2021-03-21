#ifndef	EYER_PLAYER_H
#define	EYER_PLAYER_H

#include <string>
#include <jni.h>

#include "EyerGLContext/EyerGLContext.hpp"
#include "MediaInfo.hpp"

namespace Eyer {

    enum EventOpenStatus
    {
        OPEN_STATUS_SUCCESS = 0,
        OPEN_STATUS_FAIL = -1,
        OPEN_STATUS_BUSY = -2
    };

    enum EventStopStatus
    {
        STOP_STATUS_SUCCESS,
        STOP_STATUS_FAIL,
        STOP_STATUS_NOT_OPEN
    };

    enum EyerVideoDecoder
    {
        SOFTWORE = 0,
        MEDIACODEC = 1
    };

    class EyerPlayerPrivate;

    class EyerPlayerCallback{
    public:
        EyerPlayerCallback();
        ~EyerPlayerCallback();

        int OnOpen       (EventOpenStatus status, MediaInfo & mediaInfo);
        int OnProgress   (double process);

    public:
        jobject callback = nullptr;
    };

    class EyerPlayerConfig
    {
    public:
        EyerVideoDecoder videoDecoder = EyerVideoDecoder::SOFTWORE;
    };

    class EyerPlayer
    {
    public:
        EyerPlayer();
        ~EyerPlayer();

        int SetSurface(jobject surface);
        int SetCallback(EyerPlayerCallback * callback);

        int Open(std::string url, const EyerPlayerConfig & playerConfig);

        int Play();
        int Pause();

        int Stop();

        int Seek(double time);

        int SwitchRepresentation(int representationId);

        int RenderInit();
        int RenderDraw(int texId);

    private:
        EyerPlayerPrivate * piml = nullptr;
    };
}

#endif