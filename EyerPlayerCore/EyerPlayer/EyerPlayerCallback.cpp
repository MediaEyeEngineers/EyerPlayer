#include "EyerPlayer.hpp"

#include "EyerJNI/EyerJNIEnvManager.h"
#include <jni.h>

namespace Eyer
{
    EyerPlayerCallback::EyerPlayerCallback()
    {

    }

    EyerPlayerCallback::~EyerPlayerCallback()
    {

    }

    int EyerPlayerCallback::OnOpen(EventOpenStatus status, MediaInfo & mediaInfo)
    {

        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerCallbackClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerCallback_ClassLoader);
        if(eyerCallbackClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID eyerCallbackMethod_onOpen = env->GetMethodID(eyerCallbackClass, "onOpen", "(III)I");
        if(eyerCallbackMethod_onOpen == nullptr){
            EyerLog("MediaCodec Thread: onOpen GetMethodID Fail\n");
        }

        int width = mediaInfo.videoStream.GetWidth();
        int height = mediaInfo.videoStream.GetHeight();

        int ret = env->CallIntMethod(callback, eyerCallbackMethod_onOpen, (int)status, width, height);

        return ret;
    }
}