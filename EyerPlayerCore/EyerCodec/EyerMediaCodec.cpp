#include "EyerCodec.hpp"

#include "EyerJNI/EyerJNIEnvManager.h"
#include <jni.h>

namespace Eyer
{
    EyerMediaCodec::EyerMediaCodec()
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();
    }

    EyerMediaCodec::~EyerMediaCodec()
    {
    }

    int EyerMediaCodec::Init(EyerAVStream & stream, jobject surface)
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

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
        jmethodID eyerMediaCodecMethod_Init = env->GetMethodID(eyerMediaCodecClass, "init", "(IILandroid/view/Surface;)I");
        if(eyerMediaCodecMethod_Init == nullptr){
            EyerLog("MediaCodec Thread: Init GetMethodID Fail\n");
        }

        int ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Init, stream.GetWidth(), stream.GetHeight(), surface);
        EyerLog("MediaCodec Thread: MediaCodec init: %d\n", ret);

        return 0;
    }

    int EyerMediaCodec::Uninit()
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if(eyerMediaCodecClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        // 查询 RecvAndRender 函数
        jmethodID eyerMediaCodecMethod_Uninit = env->GetMethodID(eyerMediaCodecClass, "uninit", "()I");
        if(eyerMediaCodecMethod_Uninit == nullptr){
            EyerLog("MediaCodec Thread: Uniinit GetMethodID Fail\n");
        }

        int ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Uninit);

        return ret;
    }

    int EyerMediaCodec::SendPacket(Eyer::EyerAVPacket * annexbPkt)
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if(eyerMediaCodecClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID eyerMediaCodecMethod_Send = env->GetMethodID(eyerMediaCodecClass, "send", "([BJ)I");
        if(eyerMediaCodecMethod_Send == nullptr){
            EyerLog("MediaCodec Thread: send GetMethodID Fail\n");
        }


        int ret = 0;

        jbyteArray jData = env->NewByteArray(annexbPkt->GetSize());
        env->SetByteArrayRegion(jData, 0, annexbPkt->GetSize(), (jbyte*)annexbPkt->GetDataPtr());
        jlong time = (jlong)(annexbPkt->GetSecPTS() * 1000);

        ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Send, jData, time);

        env->DeleteLocalRef(jData);

        return ret;
    }

    int EyerMediaCodec::RecvFrameRender()
    {
        int ret = 0;

        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

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





    int EyerMediaCodec::DequeueOutputBuffer()
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        int ret = 0;

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if(eyerMediaCodecClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        // 查询 dequeueOutputBuffer 函数
        jmethodID eyerMediaCodecMethod_DequeueOutputBuffer = env->GetMethodID(eyerMediaCodecClass, "dequeueOutputBuffer", "()I");
        if(eyerMediaCodecMethod_DequeueOutputBuffer == nullptr){
            EyerLog("MediaCodec Thread: DequeueOutputBuffer GetMethodID Fail\n");
        }

        ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_DequeueOutputBuffer);

        return ret;
    }

    long EyerMediaCodec::GetOutTime()
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if(eyerMediaCodecClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        // 查询 getOutTime 函数
        jmethodID eyerMediaCodecMethod_getOutTime = env->GetMethodID(eyerMediaCodecClass, "getOutTime", "()J");
        if(eyerMediaCodecMethod_getOutTime == nullptr){
            EyerLog("MediaCodec Thread: GetTime GetMethodID Fail\n");
        }

        long ret = env->CallLongMethod(eyerMediaCodec, eyerMediaCodecMethod_getOutTime);

        return ret;
    }

    int EyerMediaCodec::RenderFrame(int outindex)
    {
        JNIEnv * env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if(eyerMediaCodecClass == nullptr){
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        // 查询 getOutTime 函数
        jmethodID eyerMediaCodecMethod_renderFrame = env->GetMethodID(eyerMediaCodecClass, "renderFrame", "(I)I");
        if(eyerMediaCodecMethod_renderFrame == nullptr){
            EyerLog("MediaCodec Thread: renderFrame GetMethodID Fail\n");
        }

        int ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_renderFrame, outindex);

        return ret;

    }
}