#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include <android/native_window_jni.h>
#include "EyerGLContext/EyerGLContext.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1init
(JNIEnv * env, jclass, jobject surface)
{
    ANativeWindow * nativeWindow = ANativeWindow_fromSurface(env, surface);

    Eyer::EyerGLContextThread * glCtx = new Eyer::EyerGLContextThread(nativeWindow);
    glCtx->Start();

    return (jlong)glCtx;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1change
(JNIEnv *, jclass, jlong glCtx, jint w, jint h)
{
    Eyer::EyerGLContextThread * glContextThread = (Eyer::EyerGLContextThread *)glCtx;
    return glContextThread->SetWH(w, h);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1uninit
(JNIEnv *, jclass, jlong glCtx)
{
    Eyer::EyerGLContextThread * glContextThread = (Eyer::EyerGLContextThread *)glCtx;
    glContextThread->Stop();
    delete glContextThread;

    return 0;
}