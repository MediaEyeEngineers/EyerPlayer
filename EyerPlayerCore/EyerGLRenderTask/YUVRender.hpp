#ifndef EYERPLAYERLIB_YUV_RENDER_H
#define EYERPLAYERLIB_YUV_RENDER_H

#include "EyerAV/EyerAV.hpp"
#include "EyerGL/EyerGL.hpp"
#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    class YUVRender
    {
    public:
        YUVRender();
        ~YUVRender();

        int Init();

        int Render(EyerAVFrame * avFrame);

    private:
        Eyer::EyerGLDraw * yuv2texture = nullptr;
        Eyer::EyerGLVAO * vao = nullptr;

        Eyer::EyerGLTexture * y = nullptr;
        Eyer::EyerGLTexture * u = nullptr;
        Eyer::EyerGLTexture * v = nullptr;
    };
}

#endif // EYERPLAYERLIB_YUV_RENDER_H