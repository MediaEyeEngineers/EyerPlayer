#ifndef EYE_LIB_OPEN_GL_FUNCTIONS_CONTEXT_H
#define EYE_LIB_OPEN_GL_FUNCTIONS_CONTEXT_H

#ifdef EYER_PLATFORM_QT

#include <QOpenGLFunctions_3_3_Core>
typedef QOpenGLFunctions_3_3_Core OpenGLFunctionsContext;

#else

namespace Eyer
{
    class OpenGLFunctionsContext 
    {

    };
}

#endif

#endif //EYE_LIB_OPEN_GL_FUNCTIONS_CONTEXT_H