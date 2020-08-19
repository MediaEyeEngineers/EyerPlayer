#include "com_eyer_eyerplayer_EyerPlayerJNI.h"
#include "EyerPlayer/EyerPlayer.hpp"
#include "JniUtil.h"
#include "EyerJNI/EyerJNIEnvManager.h"

JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_videoview_1context_1init
(JNIEnv *, jclass, jobject)
{
    return 0L;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_videoview_1context_1change
(JNIEnv *, jclass, jlong, jint, jint)
{
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_videoview_1context_1uninit
(JNIEnv *, jclass, jlong)
{
    return 0;
}
