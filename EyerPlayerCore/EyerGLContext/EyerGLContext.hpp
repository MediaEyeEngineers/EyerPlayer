#ifndef	EYER_LIB_GL_CONTEXT_THREAD_AV_H
#define	EYER_LIB_GL_CONTEXT_THREAD_AV_H

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"

#include "EyerGL/EyerGL.hpp"
#include "EyerGL/GLHeader.h"

namespace Eyer
{
    class EyerGLContextThread : public EyerThread {
    public:
#ifdef EYER_PLATFORM_ANDROID
        EyerGLContextThread(ANativeWindow * nativeWindow);
#else
        EyerGLContextThread();
#endif
        ~EyerGLContextThread();
        virtual void Run();

        int SetWH(int w, int h);

        int AddRenderTask(EyerGLRenderTask * task);

        int GetW();
        int GetH();

    private:
#ifdef EYER_PLATFORM_ANDROID
        ANativeWindow * nativeWindow = nullptr;
#else
        GLFWwindow * window = nullptr;
#endif

        int w = 0;
        int h = 0;

        EyerLockQueue<EyerGLRenderTask> taskQueue;
    };
}

#endif //EYER_LIB_GL_CONTEXT_THREAD_AV_H
