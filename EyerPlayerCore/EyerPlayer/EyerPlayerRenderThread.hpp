#ifndef EYERPLAYER_EYERPLAYERRENDERTHREAD_HPP
#define EYERPLAYER_EYERPLAYERRENDERTHREAD_HPP

#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerPlayer.hpp"

namespace Eyer
{
    class EyerPlayerRenderThread : public EyerGLContextThread
    {
    public:
        EyerPlayerRenderThread(ANativeWindow * nativeWindow, EyerPlayer * player);
        ~EyerPlayerRenderThread();

        virtual int Render();

    private:
        EyerPlayer * player = nullptr;
    };
}


#endif //EYERPLAYER_EYERPLAYERRENDERTHREAD_HPP
