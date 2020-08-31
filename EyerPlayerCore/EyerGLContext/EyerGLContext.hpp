#ifndef	EYER_LIB_GL_CONTEXT_THREAD_AV_H
#define	EYER_LIB_GL_CONTEXT_THREAD_AV_H

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"

#include "EyerGL/EyerGL.hpp"
#include "EyerGL/GLHeader.h"

namespace Eyer
{
    class EyerGLContextThread;

    class EyerGLContext
    {
    public:
        EyerGLContext();
        ~EyerGLContext();

        int Init(ANativeWindow * nativeWindow);
        int Uninit();

        int MakeCurrent();
        int SwapBuffers();

        int StartGLThread();
        int StopGLThread();

    private:
        EGLContext mEglContext;
        EGLConfig eglConfig;
        EGLSurface window;
        EGLDisplay mEglDisplay;

        EyerGLContextThread * glThread = nullptr;
    };

    class EyerGLContextThread : public EyerThread {
    public:
        EyerGLContextThread(EyerGLContext * glCtx);
        ~EyerGLContextThread();
        virtual void Run();

        int SetWH(int w, int h);

        int AddRenderTask(EyerGLRenderTask * task);

        int GetW();
        int GetH();

    private:
        EyerGLContext * glCtx = nullptr;

        int w = 0;
        int h = 0;

        EyerLockQueue<EyerGLRenderTask> taskQueue;
    };
}

#endif //EYER_LIB_GL_CONTEXT_THREAD_AV_H
