#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1init
(JNIEnv *, jclass)
{
    return 0L;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1change
(JNIEnv *, jclass, jlong, jint, jint)
{
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_gl_1context_1uninit
(JNIEnv *, jclass, jlong)
{
    return 0;
}