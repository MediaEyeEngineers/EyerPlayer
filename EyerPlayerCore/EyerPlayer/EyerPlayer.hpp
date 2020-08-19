#ifndef	EYER_PLAYER_H
#define	EYER_PLAYER_H

#include <string>
#include "EyerGLContext/EyerGLContext.hpp"

namespace Eyer {

    enum EventOpenStatus
    {
        OPEN_STATUS_SUCCESS = 1,
        OPEN_STATUS_FAIL = 2,
        OPEN_STATUS_BUSY = -1
    };

    enum EventStopStatus
    {
        STOP_STATUS_SUCCESS,
        STOP_STATUS_FAIL,
        STOP_STATUS_NOT_OPEN
    };

    class EyerPlayerPrivate;


    class EyerPlayer
    {
    public:
        EyerPlayer();
        ~EyerPlayer();

        int BindGLContext(Eyer::EyerGLContextThread * ctx);
        int UnBindGLContext();

        int SetSurface();

        int Open(std::string url);

        int Play();
        int Pause();

        int Stop();

    private:
        EyerPlayerPrivate * piml = nullptr;
    };
}

#endif