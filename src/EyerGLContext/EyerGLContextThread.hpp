#ifndef	EYER_LIB_GL_CONTEXT_THREAD_AV_H
#define	EYER_LIB_GL_CONTEXT_THREAD_AV_H

#include "EyerThread/EyerThread.hpp"

#include "EyerGL/EyerGL.hpp"
#include "EyerGL/GLHeader.hpp"

#include "EyerGLCtx.hpp"
#include "EyerGLSurface.hpp"

namespace Eyer
{
#ifdef EYER_PLATFORM_ANDROID
    typedef ANativeWindow* EyerGLWindows;
#else
    typedef void* EyerGLWindows;
#endif

#ifdef EYER_PLATFORM_ANDROID
    typedef EGLBoolean (EGLAPIENTRYP EGL_PRESENTATION_TIME_ANDROIDPROC)(EGLDisplay display, EGLSurface surface, khronos_stime_nanoseconds_t time);
#else
#endif

    class EyerGLContextThreadPrivate;

    class EyerGLContextThread : public EyerThread
    {
    public:
        EyerGLContextThread();
        ~EyerGLContextThread();

        virtual void Run();

        int Init();
        virtual int Render() = 0;
        int Uninit();

        int SetWH(int w, int h);
        int GetW();
        int GetH();

        EyerGLSurface * CreateSurface   (EyerGLWindows windows);
        int MakeCurrent                 (EyerGLSurface * surface);
        int SwapBuffers                 (EyerGLSurface * surface);
        int DestroySurface              (EyerGLSurface * surface);

#ifdef EYER_PLATFORM_ANDROID
        EGL_PRESENTATION_TIME_ANDROIDPROC eglPresentationTimeANDROID = NULL;
        int SetPresentationTime         (EyerGLSurface * surface, long long nsecs);
#else
#endif

    public:
        EyerGLCtx ctx;
        EyerGLContextThreadPrivate * piml = nullptr;
    };

}

#endif //EYER_LIB_GL_CONTEXT_THREAD_AV_H
