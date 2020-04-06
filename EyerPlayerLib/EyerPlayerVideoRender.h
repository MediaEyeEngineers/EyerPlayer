#ifndef EYERPLAYERVIDEORENDER_H
#define EYERPLAYERVIDEORENDER_H

#include "EyerGL/EyerGL.hpp"
#include "EyerAV/EyerAV.hpp"

namespace EyerPlayer {
    class EyerPlayerVideoRender : public Eyer::EyerGLComponent
    {
    public:
        EyerPlayerVideoRender(EyerGLContext * _ctx);
        ~EyerPlayerVideoRender();

        int SetFrame(Eyer::EyerAVFrame * f);
        int SetMVP(Eyer::EyerMat4x4 & mvp);

        virtual int Draw();

    private:
        EyerGLContext * ctx = nullptr;
        Eyer::EyerGLDraw * frameDraw = nullptr;
        Eyer::EyerGLVAO * vao = nullptr;

        Eyer::EyerAVFrame * frame = nullptr;

        Eyer::EyerGLTexture * yT = nullptr;
        Eyer::EyerGLTexture * uT = nullptr;
        Eyer::EyerGLTexture * vT = nullptr;

        Eyer::EyerMat4x4 mvp;
    };
}

#endif // EYERPLAYERVIDEORENDER_H
