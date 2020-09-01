//
// Created by lichi on 2020/9/1.
//

#ifndef EYERPLAYER_TEXTURERENDERTASK_HPP
#define EYERPLAYER_TEXTURERENDERTASK_HPP

#include "EyerGL/EyerGL.hpp"
#include "EyerAV/EyerAV.hpp"

namespace Eyer {
    class TextureRenderTask : public Eyer::EyerGLRenderTask {
    public:
        TextureRenderTask();
        ~TextureRenderTask();

        int Render();
        int Init();
        int Destory();

        int SetTexId(int texId);

    private:
        Eyer::EyerGLDraw * textureDraw = nullptr;

        Eyer::EyerGLVAO * vao = nullptr;

        int texId = 0;
    };
}


#endif //EYERPLAYER_TEXTURERENDERTASK_HPP
