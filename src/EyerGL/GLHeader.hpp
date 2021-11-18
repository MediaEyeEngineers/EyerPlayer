#ifndef EYE_LIB_GLHEADER_H
#define EYE_LIB_GLHEADER_H

#define	EYER_STRINGIZE(x)	#x
#define	EYER_GL_SHADER(shader) "" EYER_STRINGIZE(shader)


#ifdef EYER_PLATFORM_QT

#include <QOpenGLFunctions_3_3_Core>
#define	EYER_GL_HEADER_SHADER(shader) "\#version 330\n" EYER_STRINGIZE(shader)

#elif EYER_PLATFORM_ANDROID

#define	EYER_GL_HEADER_SHADER(shader) "\#version 300 es\nprecision highp float;\n" EYER_STRINGIZE(shader)

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>

#elif EYER_PLATFORM_IOS

#define	EYER_GL_HEADER_SHADER(shader) "\#version 300 es\nprecision highp float;\n" EYER_STRINGIZE(shader)

#import <OpenGLES/gltypes.h>
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#elif EYER_PLATFORM_EMSCRIPTEN

#include <emscripten.h>
#include <SDL.h>
#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#define	EYER_GL_HEADER_SHADER(shader) "\#version 330\n" EYER_STRINGIZE(shader)

#else

#include "glad/glad.h"
#define	EYER_GL_HEADER_SHADER(shader) "\#version 330\n" EYER_STRINGIZE(shader)

#endif


#endif //EYE_LIB_GLHEADER_H
