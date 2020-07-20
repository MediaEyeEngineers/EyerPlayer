#ifndef EYE_LIB_GLHEADER_H
#define EYE_LIB_GLHEADER_H

#ifdef QT_EYER_PLAYER
#else
#endif

#ifdef QT_EYER_PLAYER

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#elif defined(EYER_PLATFORM_ANDROID)

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#else

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#endif


#endif //EYE_LIB_GLHEADER_H