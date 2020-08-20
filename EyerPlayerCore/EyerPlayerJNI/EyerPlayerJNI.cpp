#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include "EyerPlayer/EyerPlayer.hpp"
#include "JniUtil.h"

#include "EyerJNI/EyerJNIEnvManager.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    Eyer::EyerJNIEnvManager::jvm = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        EyerLog("JavaVM GetEnv Fail\n");
        return -1;
    }


    // 初始化 MediaCodec 的 class loader
    jclass eyerMediaCodec_ClassLoaderClass = env->FindClass("com/eyer/eyerplayer/codec/EyerMediaCodec");
    if(eyerMediaCodec_ClassLoaderClass == nullptr){
        EyerLog("FFFFF Find EyerMediaCodec Class Fail\n");
    }

    jmethodID eyerMediaCodec_InitMethodId = env->GetMethodID(eyerMediaCodec_ClassLoaderClass, "<init>", "()V");
    if(eyerMediaCodec_InitMethodId == nullptr){
        EyerLog("FFFFF GetMethodID Fail\n");
    }

    jobject eyerMediaCodec = env->NewObject(eyerMediaCodec_ClassLoaderClass, eyerMediaCodec_InitMethodId);
    if(eyerMediaCodec == nullptr){
        EyerLog("FFFFF NewObject Fail\n");
    }

    Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader = env->NewGlobalRef(eyerMediaCodec);

    env->DeleteLocalRef(eyerMediaCodec_ClassLoaderClass);
    env->DeleteLocalRef(eyerMediaCodec);



    EyerLog("JavaVM GetEnv Success\n");
    return JNI_VERSION_1_6;
}

JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1init
(JNIEnv * env, jclass)
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

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1set_1surface
(JNIEnv * env, jclass, jlong playerJNI, jobject surface)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    jobject surfaceRef = env->NewGlobalRef(surface);
    player->SetSurface(surfaceRef);

    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1set_1callback
(JNIEnv *, jclass, jlong playerJNI, jobject callback)
{
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;

    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1open
(JNIEnv * env, jclass, jlong playerJNI, jstring urlJNI)
{
    char * url = jstringtochar(env, urlJNI);
    Eyer::EyerPlayer * player = (Eyer::EyerPlayer *)playerJNI;
    int ret = player->Open(url);
    free(url);
    return ret;
}