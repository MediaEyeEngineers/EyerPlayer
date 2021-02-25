#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include "EyerPlayer/EyerPlayer.hpp"
#include "JniUtil.h"

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1render_1init
(JNIEnv *, jclass, jlong playerJNI)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    return player->RenderInit();
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1render_1draw
(JNIEnv *, jclass, jlong playerJNI, jint texId)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    return player->RenderDraw(texId);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1render_1uninit
(JNIEnv *, jclass, jlong playerJNI)
{
    return 0;
}