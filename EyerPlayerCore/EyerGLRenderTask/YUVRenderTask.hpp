#ifndef EYERPLAYERLIB_YUV_RENDER_TASK_H
#define EYERPLAYERLIB_YUV_RENDER_TASK_H

#include "EyerGL/EyerGL.hpp"
#include "EyerAV/EyerAV.hpp"

namespace EyerPlayer {
    class YUVRenderTask : public Eyer::EyerGLRenderTask
    {
    public:
        YUVRenderTask();
        ~YUVRenderTask();

        int SetFrame(Eyer::EyerAVFrame * videoFrame);

        int Render();
        int Init();
        int Destory();

    private:
        Eyer::EyerGLDraw * yuv2texture = nullptr;
        Eyer::EyerGLVAO * vao = nullptr;

        Eyer::EyerAVFrame * videoFrame = nullptr;

        Eyer::EyerGLTexture * y = nullptr;
        Eyer::EyerGLTexture * u = nullptr;
        Eyer::EyerGLTexture * v = nullptr;
    };
}

#endif // EYERPLAYERLIB_YUV_RENDER_TASK_H