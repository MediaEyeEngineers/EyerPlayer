#include "EyerGLContext.hpp"

#include "EyerGLContextThread.hpp"
#include "EyerGLContextThreadPrivate.hpp"

#include "EyerGL/GLHeader.hpp"

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
        const EGLint attrib_config_list[] = {
                EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES3_BIT,
                EGL_SURFACE_TYPE,       EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
                EGL_BLUE_SIZE,          8,
                EGL_GREEN_SIZE,         8,
                EGL_RED_SIZE,           8,
                EGL_ALPHA_SIZE,         8,
                // EGL_EXT_image_gl_colorspace,         EGL_EXT_gl_colorspace_scrgb_linear,
                EGL_NONE
        };
        const EGLint attrib_ctx_list[] = {
                EGL_CONTEXT_CLIENT_VERSION, 3,
                EGL_NONE
        };
        EGLint num_config;
        ctx.mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (ctx.mEglDisplay == EGL_NO_DISPLAY) {
            EyerLog("eglGetDisplay error\n");
            EyerLog("SvGLContextThread End\n");
            return -1;
        }
        if (!eglInitialize(ctx.mEglDisplay, 0, 0)) {
            EyerLog("eglInitialize() returned error %d\n", eglGetError());
            EyerLog("SvGLContextThread End\n");
            return -1;
        }
        if (!eglChooseConfig(ctx.mEglDisplay, attrib_config_list, &ctx.eglConfig, 1, &num_config)) {
            EyerLog("eglChooseConfig error\n");
            EyerLog("SvGLContextThread End\n");
            return -1;
        }
        ctx.mEglContext = eglCreateContext(ctx.mEglDisplay, ctx.eglConfig, NULL, attrib_ctx_list);
        if (ctx.mEglContext == EGL_NO_CONTEXT) {
            EyerLog("eglCreateContext error %d\n", eglGetError());
            EyerLog("SvGLContextThread End\n");
            return -1;
        }

        eglPresentationTimeANDROID = (EGL_PRESENTATION_TIME_ANDROIDPROC) eglGetProcAddress("eglPresentationTimeANDROID");

        return 0;
    }

    int EyerGLContextThread::Uninit()
    {
        eglDestroyContext(ctx.mEglDisplay, ctx.mEglContext);
        eglTerminate(ctx.mEglDisplay);

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
        surface->eglSurface = eglCreateWindowSurface(ctx.mEglDisplay, ctx.eglConfig, windows, NULL);
        return surface;
    }

    int EyerGLContextThread::MakeCurrent                 (EyerGLSurface * surface)
    {
        return eglMakeCurrent(ctx.mEglDisplay, surface->eglSurface, surface->eglSurface, ctx.mEglContext);
    }

    int EyerGLContextThread::SwapBuffers                 (EyerGLSurface * surface)
    {
        return eglSwapBuffers(ctx.mEglDisplay, surface->eglSurface);
    }

    int EyerGLContextThread::DestroySurface              (EyerGLSurface * surface)
    {
        eglDestroySurface(ctx.mEglDisplay, surface->eglSurface);
        if(surface != nullptr){
            delete surface;
            surface = nullptr;
        }
        return 0;
    }

    int EyerGLContextThread::SetPresentationTime         (EyerGLSurface * surface, long long nsecs)
    {
        eglPresentationTimeANDROID(ctx.mEglDisplay, surface->eglSurface, nsecs);
        return 0;
    }
}