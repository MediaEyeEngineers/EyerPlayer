#ifndef	EYER_LIB_GL_CONTEXT_GL_CTX_AV_H
#define	EYER_LIB_GL_CONTEXT_GL_CTX_AV_H

namespace Eyer
{
    class EyerGLCtx
    {
    public:
#ifdef EYER_PLATFORM_ANDROID
        EGLContext mEglContext;
        EGLConfig eglConfig;
        EGLDisplay mEglDisplay;
#else
        void * context = nullptr;
#endif
    };
}

#endif //EYER_LIB_GL_CONTEXT_GL_CTX_AV_H