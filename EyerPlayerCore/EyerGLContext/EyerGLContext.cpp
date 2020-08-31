#include "EyerGLContext.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer {
    EyerGLContext::EyerGLContext() {

    }

    EyerGLContext::~EyerGLContext() {

    }

    int EyerGLContext::Init(ANativeWindow *nativeWindow) {
        EyerLog("EyerGLContext Init\n");

        const EGLint attrib_config_list[] = {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_ALPHA_SIZE, 8,
                EGL_NONE
        };

        const EGLint attrib_ctx_list[] = {
                EGL_CONTEXT_CLIENT_VERSION, 3,
                EGL_NONE
        };


        EGLint num_config;

        mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (mEglDisplay == EGL_NO_DISPLAY) {
            EyerLog("eglGetDisplay error\n");
            EyerLog("EyerGLContextThread End\n");
            return -1;
        }
        if (!eglInitialize(mEglDisplay, 0, 0)) {
            EyerLog("eglInitialize() returned error %d\n", eglGetError());
            EyerLog("EyerGLContextThread End\n");
            return -1;
        }

        if (!eglChooseConfig(mEglDisplay, attrib_config_list, &eglConfig, 1, &num_config)) {
            EyerLog("eglChooseConfig error\n");
            EyerLog("EyerGLContextThread End\n");
            return -1;
        }

        mEglContext = eglCreateContext(mEglDisplay, eglConfig, NULL, attrib_ctx_list);
        if (mEglContext == EGL_NO_CONTEXT) {
            EyerLog("eglCreateContext error %d\n", eglGetError());
            EyerLog("EyerGLContextThread End\n");
            return -1;
        }

        window = eglCreateWindowSurface(mEglDisplay, eglConfig, nativeWindow, NULL);
        if (window == EGL_NO_SURFACE) {
            EyerLog("eglCreateWindowSurface error %d\n", eglGetError());
            EyerLog("EyerGLContextThread End\n");
            return -1;
        }

        return 0;
    }

    int EyerGLContext::Uninit() {
        EyerLog("EyerGLContext Uninit\n");

        StopGLThread();

        eglDestroySurface(mEglDisplay, window);
        eglDestroyContext(mEglDisplay, mEglContext);
        eglTerminate(mEglDisplay);

        return 0;
    }

    int EyerGLContext::MakeCurrent()
    {
        eglMakeCurrent(mEglDisplay, window, window, mEglContext);
        return 0;
    }

    int EyerGLContext::SwapBuffers()
    {
        eglSwapBuffers(mEglDisplay, window);
        return 0;
    }

    int EyerGLContext::StartGLThread()
    {
        if(glThread != nullptr){
            glThread->Stop();
            delete glThread;
            glThread = nullptr;
        }

        glThread = new EyerGLContextThread(this);
        glThread->Start();

        return 0;
    }

    int EyerGLContext::StopGLThread()
    {
        if(glThread != nullptr){
            glThread->Stop();
            delete glThread;
            glThread = nullptr;
        }

        return 0;
    }
}