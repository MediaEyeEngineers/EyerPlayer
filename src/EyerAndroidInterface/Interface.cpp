#include "com_zzsin_eyerplayer_jni_EyerPlayerJNI.h"

#include "EyerPlayer/EyerPlayer.hpp"
#include "EyerJNI/EyerJNIHeader.hpp"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM * vm, void * reserved)
{
    EyerLog("JavaVM GetEnv Success\n");

    JNIEnv * env = nullptr;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        EyerLog("JavaVM GetEnv Fail\n");
        return -1;
    }

    Eyer::EyerJNIEnvManager::Init(vm, env, "com/zzsin/eyerplayer/jni/EyerClazzLoader");

    return JNI_VERSION_1_6;
}

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
    // return player->SetURL("https://www.zzsin.com/hdr/V/ysjf.m3u8");
    return player->SetURL("https://www.zzsin.com/hdr/ZhongLi.mp4");
    // return player->SetURL("rtmp://av.zzsin.com/abc/abc/abcdefg.flv");
    // return player->SetURL("rtmp://124.237.177.17:8222/myapp/sdkplay");
    // return player->SetURL("rtmp://playrtmp-xiaodu.superkd.cn/xiaodu/obs.flv ");
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