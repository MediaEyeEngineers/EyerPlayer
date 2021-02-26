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
        EyerGLContextThread(ANativeWindow * nativeWindow);
        ~EyerGLContextThread();

        virtual void Run();

        virtual int Render() = 0;

        int SetWH(int w, int h);

        int GetW();
        int GetH();

        int SwapBuffers();

    private:
        ANativeWindow * nativeWindow = nullptr;

        EGLContext mEglContext;
        EGLConfig eglConfig;
        EGLSurface window;
        EGLDisplay mEglDisplay;

        int w = 0;
        int h = 0;
    };
}

#endif //EYER_LIB_GL_CONTEXT_THREAD_AV_H
