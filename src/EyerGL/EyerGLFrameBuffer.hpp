#ifndef EYERLIB_EYERGLFRAMEBUFFER_HPP
#define EYERLIB_EYERGLFRAMEBUFFER_HPP

#include "EyerGLTexture.hpp"
#include "EyerGLComponent.hpp"
#include "EyerGLFrameBufferParams.hpp"
#include "OpenGLFunctionsContext.hpp"

#include <vector>

namespace Eyer
{
    enum class EyerGLFrameBufferTarget
    {
        SCREEN,
        TEXTURE
    };

    class EyerGLFrameBuffer
    {
    public:
        EyerGLFrameBuffer(const EyerGLFrameBufferParams & params, EyerGLTexture * _texture = nullptr, unsigned int _defaultFBO = 0,  OpenGLFunctionsContext * _funcCtx = nullptr);
        ~EyerGLFrameBuffer();

        int SetParams(const EyerGLFrameBufferParams & params);
        int SetParams(int width, int height);

        int AddComponent(EyerGLComponent * component);
        int RemoveAllComponent();

        int Render();

        int ReadPixel(int x, int y, int width, int height, unsigned char * data);

        int GetWidth();
        int GetHeight();

    public:
        unsigned int defaultFBO = 0;
        unsigned int fbo = 0;
        EyerGLFrameBufferParams params;
        EyerGLFrameBufferTarget mode = EyerGLFrameBufferTarget::SCREEN;
        std::vector<EyerGLComponent *> componentList;

    private:
        EyerGLFrameBuffer(const EyerGLFrameBuffer & frameBuffer) = delete;
        const EyerGLFrameBuffer & operator = (const EyerGLFrameBuffer & frameBuffer) = delete;

        OpenGLFunctionsContext * funcCtx = nullptr;
    };
}

#endif //EYERLIB_EYERGLFRAMEBUFFER_HPP
