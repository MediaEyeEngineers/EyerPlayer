#include "com_zzsin_eyerplayer_jni_EyerPlayerJNI.h"

#include "EyerPlayer/EyerPlayer.hpp"

JNIEXPORT jlong JNICALL Java_com_zzsin_eyerplayer_jni_EyerPlayerJNI_eyer_1player_1init
(JNIEnv *, jclass)
{
    Eyer::EyerPlayer * player = new Eyer::EyerPlayer();
    return (jlong)player;
}

JNIEXPORT jint JNICALL Java_com_zzsin_eyerplayer_jni_EyerPlayerJNI_eyer_1player_1uninit
(JNIEnv *, jclass, jlong playerJNI)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    delete player;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_zzsin_eyerplayer_jni_EyerPlayerJNI_eyer_1player_1set_1url
(JNIEnv *, jclass, jlong playerJNI, jstring urlJNI)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    return player->SetURL("https://www.zzsin.com/hdr/V/ysjf.m3u8");
}

JNIEXPORT jint JNICALL Java_com_zzsin_eyerplayer_jni_EyerPlayerJNI_eyer_1player_1play
(JNIEnv *, jclass, jlong playerJNI)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    return player->Play();
}

JNIEXPORT jint JNICALL Java_com_zzsin_eyerplayer_jni_EyerPlayerJNI_eyer_1player_1stop
(JNIEnv *, jclass, jlong playerJNI)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    return player->Stop();
}

JNIEXPORT jint JNICALL Java_com_zzsin_eyerplayer_jni_EyerPlayerJNI_eyer_1player_1pause
(JNIEnv *, jclass, jlong playerJNI)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    return player->Pause();
}

JNIEXPORT jint JNICALL Java_com_zzsin_eyerplayer_jni_EyerPlayerJNI_eyer_1player_1resume
(JNIEnv *, jclass, jlong playerJNI)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    return player->Resume();
}