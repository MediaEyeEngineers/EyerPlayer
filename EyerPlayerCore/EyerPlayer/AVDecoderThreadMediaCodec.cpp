#include "EyerPlayerThread.hpp"
#include "EventTag.hpp"

#include "EyerJNI/EyerJNIEnvManager.h"
#include <jni.h>

namespace EyerPlayer {
    AVDecoderThreadMediaCodec::AVDecoderThreadMediaCodec(Eyer::EyerAVStream & _stream, AVFrameQueueManager * _frameQueueManager)
            : AVDecoderThread(_stream, _frameQueueManager)
    {

    }

    AVDecoderThreadMediaCodec::~AVDecoderThreadMediaCodec()
    {

    }

    void AVDecoderThreadMediaCodec::Run()
    {
        EyerLog("AVDecoder Software Thread Start\n");

        JNIEnv * env = nullptr;
        Eyer::EyerJNIEnvManager::jvm->AttachCurrentThread(&env, 0);
        if(env == nullptr){

        }

        jclass eyerMediaCodec = env->FindClass("com/eyer/eyerplayer/codec/EyerMediaCodec");
        


        EyerLog("AVDecoder Software Thread Stop\n");
    }
}