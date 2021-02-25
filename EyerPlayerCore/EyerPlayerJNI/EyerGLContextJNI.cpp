#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerGLRenderTask/TextureRenderTask.hpp"

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