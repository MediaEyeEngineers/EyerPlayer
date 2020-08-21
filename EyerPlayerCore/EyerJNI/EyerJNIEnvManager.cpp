#include "EyerJNIEnvManager.h"

#include "EyerCore/EyerCore.hpp"

namespace Eyer{
    JavaVM * EyerJNIEnvManager::jvm = nullptr;
    jobject EyerJNIEnvManager::eyerMediaCodec_ClassLoader = nullptr;
    jobject EyerJNIEnvManager::eyerCallback_ClassLoader = nullptr;

    JNIEnv * EyerJNIEnvManager::AttachCurrentThread()
    {
        JNIEnv * env = nullptr;
        int status = Eyer::EyerJNIEnvManager::jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status < 0) {
            Eyer::EyerJNIEnvManager::jvm->AttachCurrentThread(&env, NULL);
        }
        if(env == nullptr) {
            EyerLog("AttachCurrentThread Fail\n");
        }

        return env;
    }
}