#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerPlayer/EyerPlayerRenderThread.hpp"
#include "EyerGLRenderTask/TextureRenderTask.hpp"
#include <android/native_window_jni.h>

Eyer::TextureRenderTask * task = nullptr;

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1gl_1init
(JNIEnv *, jclass)
{
    task = new Eyer::TextureRenderTask();
    task->Init();
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1gl_1draw
(JNIEnv *, jclass, jint texId)
{
    task->SetTexId(texId);
    task->Render();
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1gl_1viewport
(JNIEnv *, jclass, jint, jint)
{
    return 0;
}









JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1gl_1ctx_1create
(JNIEnv * env, jclass, jobject surface, jlong playerJNI)
{
    ANativeWindow * nativeWindow = ANativeWindow_fromSurface(env, surface);
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;

    Eyer::EyerPlayerRenderThread * ctx = new Eyer::EyerPlayerRenderThread(nativeWindow, player);
    ctx->Start();
    return (jlong)ctx;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1gl_1ctx_1set_1wh
(JNIEnv *, jclass, jlong ctxJNI, jint w, jint h)
{
    Eyer::EyerPlayerRenderThread * ctx = (Eyer::EyerPlayerRenderThread *)ctxJNI;
    return ctx->SetWH(w, h);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1gl_1ctx_1destroyed
(JNIEnv *, jclass, jlong ctxJNI)
{
    Eyer::EyerPlayerRenderThread * ctx = (Eyer::EyerPlayerRenderThread *)ctxJNI;
    delete ctx;
    return 0;
}