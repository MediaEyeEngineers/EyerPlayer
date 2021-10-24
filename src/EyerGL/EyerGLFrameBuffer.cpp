#include "EyerGLFrameBuffer.hpp"

#include "EyerGLTexture.hpp"
#include "GLHeader.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerGLFrameBuffer::EyerGLFrameBuffer(const EyerGLFrameBufferParams & _params, EyerGLTexture * _texture, unsigned int _defaultFBO)
    {
        SetParams(_params);
        if(_texture == nullptr){
            // 渲染到屏幕
            mode = EyerGLFrameBufferTarget::SCREEN;
            defaultFBO = _defaultFBO;
            fbo = defaultFBO;
        }
        else {
            // 渲染到纹理
            mode = EyerGLFrameBufferTarget::TEXTURE;

            glGenFramebuffers(1, &fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);

            _texture->SetDataRGBAChannel(nullptr, GetWidth(), GetHeight());

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->textureId, 0);

            GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (status == GL_FRAMEBUFFER_COMPLETE) {
                EyerLog("Single FBO setup successfully.\n");
            }
            else if(status == GL_FRAMEBUFFER_UNDEFINED){
                EyerLog("Problem GL_FRAMEBUFFER_UNDEFINED: %d .\n", status);
            }
            else if(status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT){
                EyerLog("Problem GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: %d .\n", status);
            }
            else if(status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT){
                EyerLog("Problem GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: %d .\n", status);
            }
            else{
                EyerLog("Problem: %d .\n", status);
            }
        }
    }

    EyerGLFrameBuffer::~EyerGLFrameBuffer()
    {
        if(mode == EyerGLFrameBufferTarget::TEXTURE){
            if(fbo != 0){
                glDeleteFramebuffers(1, &fbo);
                fbo = 0;
            }
        }
    }

    int EyerGLFrameBuffer::SetParams(int width, int height)
    {
        params.width    = width;
        params.height   = height;
        return 0;
    }

    int EyerGLFrameBuffer::SetParams(const EyerGLFrameBufferParams & _params)
    {
        params = _params;
        return 0;
    }

    int EyerGLFrameBuffer::GetWidth()
    {
        return params.width;
    }

    int EyerGLFrameBuffer::GetHeight()
    {
        return params.height;
    }

    int EyerGLFrameBuffer::Render()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glViewport(0, 0, params.width, params.height);
        glClearColor(params.color.x(), params.color.y(), params.color.z(), params.color.w());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(int i=0; i<componentList.size(); i++){
            componentList[i]->Draw();
        }

        return 0;
    }

    int EyerGLFrameBuffer::AddComponent(EyerGLComponent * component)
    {
        componentList.push_back(component);
        return 0;
    }

    int EyerGLFrameBuffer::ReadPixel(int x, int y, int width, int height, unsigned char * data)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return 0;
    }
}