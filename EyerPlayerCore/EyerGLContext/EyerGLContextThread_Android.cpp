#include "EyerGLContext.hpp"

namespace Eyer
{
    EyerGLContextThread::EyerGLContextThread(ANativeWindow * _nativeWindow)
    {
        nativeWindow = _nativeWindow;
    }

    EyerGLContextThread::~EyerGLContextThread()
    {

    }

    void EyerGLContextThread::Run()
    {
        EyerLog("EyerGLContextThread Start\n");

        const EGLint attrib_config_list[] = {
                EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES3_BIT,
                EGL_SURFACE_TYPE,       EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
                EGL_BLUE_SIZE,          8,
                EGL_GREEN_SIZE,         8,
                EGL_RED_SIZE,           8,
                EGL_ALPHA_SIZE,         8,
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
            SetStoping();
            return;
        }
        if (!eglInitialize(mEglDisplay, 0, 0)) {
            EyerLog("eglInitialize() returned error %d\n", eglGetError());
            EyerLog("EyerGLContextThread End\n");
            SetStoping();
            return;
        }

        if (!eglChooseConfig(mEglDisplay, attrib_config_list, &eglConfig, 1, &num_config)) {
            EyerLog("eglChooseConfig error\n");
            EyerLog("EyerGLContextThread End\n");
            SetStoping();
            return;
        }

        mEglContext = eglCreateContext(mEglDisplay, eglConfig, NULL, attrib_ctx_list);
        if (mEglContext == EGL_NO_CONTEXT) {
            EyerLog("eglCreateContext error %d\n", eglGetError());
            EyerLog("EyerGLContextThread End\n");
            SetStoping();
            return;
        }

        window = eglCreateWindowSurface(mEglDisplay, eglConfig, nativeWindow, NULL);
        if(window == EGL_NO_SURFACE) {
            EyerLog("eglCreateWindowSurface error %d\n", eglGetError());
            EyerLog("EyerGLContextThread End\n");
            SetStoping();
            return;
        }

        eglMakeCurrent(mEglDisplay, window, window, mEglContext);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        Render();

        /*
        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        */

        eglDestroySurface(mEglDisplay, window);
        eglDestroyContext(mEglDisplay, mEglContext);
        eglTerminate(mEglDisplay);

        EyerLog("EyerGLContextThread End\n");
    }

    int EyerGLContextThread::SwapBuffers()
    {
        eglSwapBuffers(mEglDisplay, window);
        return 0;
    }

    int EyerGLContextThread::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }

    int EyerGLContextThread::GetW()
    {
        return w;
    }

    int EyerGLContextThread::GetH()
    {
        return h;
    }
}