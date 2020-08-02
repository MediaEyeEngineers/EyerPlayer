#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include "EyerPlayer/EyerPlayer.hpp"
#include "JniUtil.h"

JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1init
(JNIEnv *, jclass)
{
    EyerPlayer::EyerPlayer * player = new EyerPlayer::EyerPlayer();
    return (jlong)player;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1uninit
(JNIEnv *, jclass, jlong playerJNI)
{
    EyerPlayer::EyerPlayer * player = (EyerPlayer::EyerPlayer *)playerJNI;
    delete player;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1open
(JNIEnv * env, jclass, jlong playerJNI, jstring urlJNI)
{
    char * url = jstringtochar(env, urlJNI);
    EyerPlayer::EyerPlayer * player = (EyerPlayer::EyerPlayer *)playerJNI;
    int ret = player->Open(url);
    free(url);
    return ret;
}


JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1set_1gl_1ctx
(JNIEnv *, jclass, jlong playerJNI, jlong glCtxJNI)
{
    EyerPlayer::EyerPlayer * player = (EyerPlayer::EyerPlayer *)playerJNI;
    Eyer::EyerGLContextThread * glContextThread = (Eyer::EyerGLContextThread *)glCtxJNI;

    return player->BindGLContext(glContextThread);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1unset_1gl_1ctx
(JNIEnv *, jclass, jlong playerJNI)
{
    EyerPlayer::EyerPlayer * player = (EyerPlayer::EyerPlayer *)playerJNI;

    return player->UnBindGLContext();
}