#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include "EyerGLContext/EyerGLContext.hpp"

#include <android/native_window_jni.h>

JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1alloc
(JNIEnv *, jclass)
{
    Eyer::EyerGLContext * glCtx = new Eyer::EyerGLContext();
    return (jlong)glCtx;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1dealloc
(JNIEnv *, jclass, jlong glCtxJNI)
{
    Eyer::EyerGLContext * glCtx = (Eyer::EyerGLContext *)glCtxJNI;
    delete glCtx;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1init
(JNIEnv * env, jclass, jlong glCtxJNI, jobject surface)
{
    Eyer::EyerGLContext * glCtx = (Eyer::EyerGLContext *)glCtxJNI;
    ANativeWindow * nativeWindow = ANativeWindow_fromSurface(env, surface);
    return glCtx->Init(nativeWindow);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1uninit
(JNIEnv *, jclass, jlong glCtxJNI)
{
    Eyer::EyerGLContext * glCtx = (Eyer::EyerGLContext *)glCtxJNI;
    return glCtx->Uninit();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1makecurrent
(JNIEnv *, jclass, jlong glCtxJNI)
{
    Eyer::EyerGLContext * glCtx = (Eyer::EyerGLContext *)glCtxJNI;
    return glCtx->MakeCurrent();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1start_1gl_1thread
(JNIEnv *, jclass, jlong glCtxJNI)
{
    Eyer::EyerGLContext * glCtx = (Eyer::EyerGLContext *)glCtxJNI;
    return glCtx->StartGLThread();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1stop_1gl_1thread
(JNIEnv *, jclass, jlong glCtxJNI)
{
    Eyer::EyerGLContext * glCtx = (Eyer::EyerGLContext *)glCtxJNI;
    return glCtx->StopGLThread();
}