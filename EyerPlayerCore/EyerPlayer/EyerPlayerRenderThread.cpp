#include "EyerPlayerRenderThread.hpp"

#include "EyerGL/EyerGL.hpp"

namespace Eyer
{
    EyerPlayerRenderThread::EyerPlayerRenderThread(ANativeWindow * nativeWindow, EyerPlayer * _player)
        : EyerGLContextThread(nativeWindow)
    {
        player = _player;
    }

    EyerPlayerRenderThread::~EyerPlayerRenderThread()
    {

    }

    int EyerPlayerRenderThread::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        player->RenderInit();
        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);
            int ret = player->RenderDraw(0);
            if(!ret){
                SwapBuffers();
            }
        }

        return 0;
    }
}