#include "EyerGLContext.hpp"

#include "EyerGLContextThread.hpp"
#include "EyerGLContextThreadPrivate.hpp"

#include "EyerGL_IOS_Context_C_Interface.h"

namespace Eyer
{
    EyerGLContextThread::EyerGLContextThread()
    {
        piml = new EyerGLContextThreadPrivate();
    }

    EyerGLContextThread::~EyerGLContextThread()
    {
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    void EyerGLContextThread::Run()
    {
        Init();
        Render();
        Uninit();
    }

    int EyerGLContextThread::Init()
    {
        EyerLog("Eyer GL Context IOS Init\n");
        ctx.context = ios_gl_ctx_init();
        return 0;
    }

    int EyerGLContextThread::Uninit()
    {
        EyerLog("Eyer GL Context IOS UnInit\n");
        if(ctx.context != nullptr){
            ios_gl_ctx_uninit(ctx.context);
            ctx.context = nullptr;
        }
        return 0;
    }

    int EyerGLContextThread::SetWH(int w, int h)
    {
        piml->width = w;
        piml->height = h;
        return 0;
    }

    int EyerGLContextThread::GetW()
    {
        return piml->width;
    }

    int EyerGLContextThread::GetH()
    {
        return piml->height;
    }

    EyerGLSurface * EyerGLContextThread::CreateSurface   (EyerGLWindows windows)
    {
        EyerGLSurface * surface = new EyerGLSurface();
        ios_gl_ctx_create_surface(ctx.context, windows, &surface->frameBuffer, &surface->colorRenderBuffer);
        return surface;
    }

    int EyerGLContextThread::MakeCurrent                 (EyerGLSurface * surface)
    {
        ios_gl_ctx_makecurrent(ctx.context, surface->frameBuffer, surface->colorRenderBuffer);
        return 0;
    }

    int EyerGLContextThread::SwapBuffers                 (EyerGLSurface * surface)
    {
        ios_gl_ctx_swapbuffers(ctx.context, surface->frameBuffer, surface->colorRenderBuffer);
        return 0;
    }

    int EyerGLContextThread::DestroySurface              (EyerGLSurface * surface)
    {
        ios_gl_ctx_destroy_surface(ctx.context, surface->frameBuffer, surface->colorRenderBuffer);
        if(surface != nullptr){
            delete surface;
            surface = nullptr;
        }
        return 0;
    }
}