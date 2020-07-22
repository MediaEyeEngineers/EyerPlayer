#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include "EyerPlayer/EyerPlayer.hpp"

JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1init
(JNIEnv *, jclass)
{
    Eyer::EyerPlayer * player = new Eyer::EyerPlayer();
    return (jlong)player;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1uninit
(JNIEnv *, jclass, jlong playerJNI)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    delete player;
    return 0;
}