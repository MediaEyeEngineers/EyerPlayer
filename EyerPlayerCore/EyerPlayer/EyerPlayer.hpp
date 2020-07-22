#ifndef	EYER_PLAYER_H
#define	EYER_PLAYER_H

#include <string>
#include "EyerGLContext/EyerGLContext.hpp"

namespace Eyer {
    class EyerPlayerPrivate;

    class EyerPlayer
    {
    public:
        EyerPlayer();
        ~EyerPlayer();

        int BindGLContext(EyerGLContextThread * ctx);
        int UnBindGLContext();

        int SetURL(std::string url);

        int Open();

        int Play();
        int Pause();

        int Stop();

    private:
        EyerPlayerPrivate * piml = nullptr;
    };
}

#endif