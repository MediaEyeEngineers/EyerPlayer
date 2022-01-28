#ifndef	EYER_LIB_GL_CONTEXT_GL_SURFACE_AV_H
#define	EYER_LIB_GL_CONTEXT_GL_SURFACE_AV_H

#include <stdio.h>
#include "EyerGL/GLHeader.hpp"

namespace Eyer
{
    class EyerGLSurface
    {
    public:
#ifdef EYER_PLATFORM_ANDROID
        EGLSurface eglSurface = nullptr;
#else
        GLuint frameBuffer = 0;
        GLuint colorRenderBuffer = 0;
#endif
    };
}

#endif //EYER_LIB_GL_CONTEXT_GL_SURFACE_AV_H