#include "EyerGLContext.hpp"

namespace Eyer
{

#ifdef EYER_PLATFORM_ANDROID
    EyerGLContextThread::EyerGLContextThread(ANativeWindow * _nativeWindow)
    {
        nativeWindow = _nativeWindow;
    }
#else
#endif

    EyerGLContextThread::~EyerGLContextThread()
    {

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

    void EyerGLContextThread::Run()
    {
        EyerLog("EyerGLContextThread Start\n");

#ifdef EYER_PLATFORM_ANDROID
        EGLContext mEglContext;
        EGLConfig eglConfig;
        EGLSurface window;
        EGLDisplay mEglDisplay;
        
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

        glClearColor(1.0, 1.0, 1.0, 1.0);
        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // glFinish();
            // eglSwapBuffers(mEglDisplay, window);
            if(taskQueue.GetSize() > 0 || renderAndFreeTaskQueue.GetSize() > 0){
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                while(taskQueue.GetSize() > 0){
                    taskQueue.PopAndRender(w, h);
                }

                // EyerLog("Queue Size: %d\n", renderAndFreeTaskQueue.GetSize());

                while(renderAndFreeTaskQueue.GetSize() > 0){
                    // EyerLog("Queue Size: %d\n", renderAndFreeTaskQueue.GetSize());
                    renderAndFreeTaskQueue.PopAndRenderAndFree(w, h);

                    glFinish();
                    eglSwapBuffers(mEglDisplay, window);
                }
                
                // glFinish();
                // eglSwapBuffers(mEglDisplay, window);
            }
        }

        while(destoryTaskQueue.Size() > 0){
            EyerGLRenderTask * task = nullptr;
            destoryTaskQueue.FrontPop(&task);
            if(task != nullptr){
                task->Destory();
            }
        }

        eglDestroySurface(mEglDisplay, window);
        eglDestroyContext(mEglDisplay, mEglContext);
        eglTerminate(mEglDisplay);

        SetStoping();

#else
#endif
        EyerLog("EyerGLContextThread End\n");
    }

    int EyerGLContextThread::AddTaskToRenderQueue(EyerGLRenderTask * task)
    {
        taskQueue.PushRendTask(task);
        return 0;
    }

    int EyerGLContextThread::AddTaskToRenderAndFreeQueue(EyerGLRenderTask * task)
    {
        // EyerLog("Queue Size: %d\n", renderAndFreeTaskQueue.GetSize());
        while(renderAndFreeTaskQueue.GetSize() > 2){
            renderAndFreeTaskQueue.PopAndFree();
        }
        renderAndFreeTaskQueue.PushRendTask(task);
        return 0;
    }

    int EyerGLContextThread::AddTaskToDestoryQueue(EyerGLRenderTask * task)
    {
        destoryTaskQueue.Push(task);
        return 0;
    }
}