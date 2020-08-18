#include "EyerCodec.hpp"

#include "EyerJNI/EyerJNIEnvManager.h"
#include <jni.h>

namespace Eyer
{
    EyerMediaCodec::EyerMediaCodec()
    {
        std::lock_guard<std::mutex> lg(mut);
        JNIEnv * env = nullptr;
        int status = Eyer::EyerJNIEnvManager::jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status < 0) {
            Eyer::EyerJNIEnvManager::jvm->AttachCurrentThread(&env, NULL);
        }
        if(env == nullptr) {
            EyerLog("AttachCurrentThread Fail\n");
        }
    }

    EyerMediaCodec::~EyerMediaCodec()
    {
        std::lock_guard<std::mutex> lg(mut);

        /*
        // 调用 Uninit 函数
        jmethodID eyerMediaCodecMethod_Uninit = decoderEnv->GetMethodID(eyerMediaCodecClass, "uninit", "()I");
        if(eyerMediaCodecMethod_Uninit == nullptr){
            EyerLog("MediaCodec Thread: Init GetMethodID Fail\n");
        }

        int ret = decoderEnv->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Uninit);
        EyerLog("MediaCodec Thread: MediaCodec uninit: %d\n", ret);
        */
    }

    int EyerMediaCodec::BindDecoderThread()
    {
        std::lock_guard<std::mutex> lg(mut);
        /*
        int status = Eyer::EyerJNIEnvManager::jvm->GetEnv((void **) &decoderEnv, JNI_VERSION_1_6);
        if (status < 0) {
            Eyer::EyerJNIEnvManager::jvm->AttachCurrentThread(&decoderEnv, NULL);
        }
        if(decoderEnv == nullptr) {
            EyerLog("AttachCurrentThread Fail\n");
        }
         */
        return 0;
    }

    int EyerMediaCodec::BindPlayCtrThread()
    {
        std::lock_guard<std::mutex> lg(mut);
        /*
        int status = Eyer::EyerJNIEnvManager::jvm->GetEnv((void **) &playctrEnv, JNI_VERSION_1_6);
        if (status < 0) {
            Eyer::EyerJNIEnvManager::jvm->AttachCurrentThread(&playctrEnv, NULL);
        }
        if(playctrEnv == nullptr) {
            EyerLog("AttachCurrentThread Fail\n");
        }
        */
        return 0;
    }

    int EyerMediaCodec::Init(EyerAVStream & stream)
    {
        std::lock_guard<std::mutex> lg(mut);

        JNIEnv * env = nullptr;
        int status = Eyer::EyerJNIEnvManager::jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status < 0) {
            Eyer::EyerJNIEnvManager::jvm->AttachCurrentThread(&env, NULL);
        }
        if(env == nullptr) {
            EyerLog("AttachCurrentThread Fail\n");
        }

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if(eyerMediaCodecClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }


        jmethodID eyerMediaCodecMethod = env->GetMethodID(eyerMediaCodecClass, "<init>", "()V");
        if(eyerMediaCodecMethod == nullptr){
            EyerLog("MediaCodec Thread: GetMethodID Fail\n");
        }


        jobject _eyerMediaCodec = env->NewObject(eyerMediaCodecClass, eyerMediaCodecMethod);
        if(_eyerMediaCodec == nullptr){
            EyerLog("MediaCodec Thread: EyerMediaCodec Class Fail\n");
        }

        eyerMediaCodec = env->NewGlobalRef(_eyerMediaCodec);


        // 调用 Init 函数
        jmethodID eyerMediaCodecMethod_Init = env->GetMethodID(eyerMediaCodecClass, "init", "(II)I");
        if(eyerMediaCodecMethod_Init == nullptr){
            EyerLog("MediaCodec Thread: Init GetMethodID Fail\n");
        }

        int ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Init, stream.GetWidth(), stream.GetHeight());
        EyerLog("MediaCodec Thread: MediaCodec init: %d\n", ret);

        return 0;
    }

    int EyerMediaCodec::SendPacket(Eyer::EyerAVPacket * annexbPkt)
    {
        std::lock_guard<std::mutex> lg(mut);

        JNIEnv * env = nullptr;
        int status = Eyer::EyerJNIEnvManager::jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status < 0) {
            Eyer::EyerJNIEnvManager::jvm->AttachCurrentThread(&env, NULL);
        }
        if(env == nullptr) {
            EyerLog("AttachCurrentThread Fail\n");
        }

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if(eyerMediaCodecClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID eyerMediaCodecMethod_Send = env->GetMethodID(eyerMediaCodecClass, "send", "([B)I");
        if(eyerMediaCodecMethod_Send == nullptr){
            EyerLog("MediaCodec Thread: send GetMethodID Fail\n");
        }


        int ret = 0;

        jbyteArray jData = env->NewByteArray(annexbPkt->GetSize());
        env->SetByteArrayRegion(jData, 0, annexbPkt->GetSize(), (jbyte*)annexbPkt->GetDataPtr());

        ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Send, jData);

        env->DeleteLocalRef(jData);

        return ret;
    }

    int EyerMediaCodec::RecvFrameRender()
    {
        std::lock_guard<std::mutex> lg(mut);

        int ret = 0;


        JNIEnv * env = nullptr;
        int status = Eyer::EyerJNIEnvManager::jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status < 0) {
            Eyer::EyerJNIEnvManager::jvm->AttachCurrentThread(&env, NULL);
        }
        if(env == nullptr) {
            EyerLog("AttachCurrentThread Fail\n");
        }

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if(eyerMediaCodecClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        // 查询 RecvAndRender 函数
        jmethodID eyerMediaCodecMethod_RecvAndRender = env->GetMethodID(eyerMediaCodecClass, "recvAndRender", "()I");
        if(eyerMediaCodecMethod_RecvAndRender == nullptr){
            EyerLog("MediaCodec Thread: recvAndRender GetMethodID Fail\n");
        }


        ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_RecvAndRender);

        return ret;
    }
}