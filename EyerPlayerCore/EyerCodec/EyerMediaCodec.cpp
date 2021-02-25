#include "EyerCodec.hpp"

#include "EyerJNI/EyerJNIEnvManager.h"
#include <jni.h>

namespace Eyer {
    EyerMediaCodec::EyerMediaCodec() {

    }

    EyerMediaCodec::~EyerMediaCodec() {

    }

    int EyerMediaCodec::Init(EyerAVStream &stream, jobject surface) {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(
                Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }


        jmethodID eyerMediaCodecMethod = env->GetMethodID(eyerMediaCodecClass, "<init>", "()V");
        if (eyerMediaCodecMethod == nullptr) {
            EyerLog("MediaCodec Thread: GetMethodID Fail\n");
        }


        jobject _eyerMediaCodec = env->NewObject(eyerMediaCodecClass, eyerMediaCodecMethod);
        if (_eyerMediaCodec == nullptr) {
            EyerLog("MediaCodec Thread: EyerMediaCodec Class Fail\n");
        }

        eyerMediaCodec = env->NewGlobalRef(_eyerMediaCodec);

        // 调用 Init 函数
        jmethodID eyerMediaCodecMethod_Init = env->GetMethodID(eyerMediaCodecClass, "init",
                                                               "(IILandroid/view/Surface;)I");
        if (eyerMediaCodecMethod_Init == nullptr) {
            EyerLog("MediaCodec Thread: Init GetMethodID Fail\n");
        }

        int ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Init, stream.GetWidth(),
                                     stream.GetHeight(), surface);
        EyerLog("MediaCodec Thread: MediaCodec init: %d\n", ret);

        return 0;
    }

    int EyerMediaCodec::Uninit() {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        // 查询 RecvAndRender 函数
        jmethodID eyerMediaCodecMethod_Uninit = env->GetMethodID(eyerMediaCodecClass, "uninit",
                                                                 "()I");
        if (eyerMediaCodecMethod_Uninit == nullptr) {
            EyerLog("MediaCodec Thread: Uniinit GetMethodID Fail\n");
        }

        int ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Uninit);

        env->DeleteLocalRef(eyerMediaCodec);

        return ret;
    }

    int EyerMediaCodec::dequeueInputBuffer(long long timeoutUs)
    {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID jmethodId = env->GetMethodID(eyerMediaCodecClass, "dequeueInputBuffer", "(J)I");
        if(jmethodId == nullptr){
            EyerLog("MediaCodec GetMethodID Fail\n");
        }

        env->DeleteLocalRef(eyerMediaCodecClass);

        return env->CallIntMethod(eyerMediaCodec, jmethodId, timeoutUs);
    }

    int EyerMediaCodec::putInputData(int index, unsigned char *data, int size)
    {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID jmethodId = env->GetMethodID(eyerMediaCodecClass, "putInputData", "(I[B)I");
        if(jmethodId == nullptr){
            EyerLog("MediaCodec GetMethodID Fail\n");
        }

        jbyteArray jData = env->NewByteArray(size);
        env->SetByteArrayRegion(jData, 0, size, (jbyte *)data);
        int ret =  env->CallIntMethod(eyerMediaCodec, jmethodId, index, jData);
        env->DeleteLocalRef(jData);

        env->DeleteLocalRef(eyerMediaCodecClass);

        return ret;
    }

    void EyerMediaCodec::queueInputBuffer(int index, int offset, int size, long long presentationTimeUs, int flags)
    {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID jmethodId = env->GetMethodID(eyerMediaCodecClass, "queueInputBuffer", "(IIIJI)V");
        if(jmethodId == nullptr){
            EyerLog("MediaCodec GetMethodID Fail\n");
        }

        env->CallVoidMethod(eyerMediaCodec, jmethodId, index, offset, size, presentationTimeUs, flags);

        env->DeleteLocalRef(eyerMediaCodecClass);
    }

    void EyerMediaCodec::sendEndOfStream(int index)
    {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID jmethodId = env->GetMethodID(eyerMediaCodecClass, "sendEndOfStream", "(I)V");
        if(jmethodId == nullptr){
            EyerLog("MediaCodec GetMethodID Fail\n");
        }

        env->CallVoidMethod(eyerMediaCodec, jmethodId, index);

        env->DeleteLocalRef(eyerMediaCodecClass);
    }









    int EyerMediaCodec::dequeueOutputBuffer(long long timeoutUs)
    {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID jmethodId = env->GetMethodID(eyerMediaCodecClass, "dequeueOutputBuffer", "(J)I");
        if(jmethodId == nullptr){
            EyerLog("MediaCodec GetMethodID Fail\n");
        }

        env->DeleteLocalRef(eyerMediaCodecClass);

        return env->CallIntMethod(eyerMediaCodec, jmethodId, timeoutUs);
    }

    long long EyerMediaCodec::getOutTime()
    {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID jmethodId = env->GetMethodID(eyerMediaCodecClass, "getOutTime", "()J");
        if(jmethodId == nullptr){
            EyerLog("MediaCodec GetMethodID Fail\n");
        }

        env->DeleteLocalRef(eyerMediaCodecClass);

        return env->CallLongMethod(eyerMediaCodec, jmethodId);
    }

    int EyerMediaCodec::releaseOutputBuffer(int index, bool render)
    {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID jmethodId = env->GetMethodID(eyerMediaCodecClass, "releaseOutputBuffer", "(IZ)I");
        if(jmethodId == nullptr){
            EyerLog("MediaCodec GetMethodID Fail\n");
        }

        env->DeleteLocalRef(eyerMediaCodecClass);

        return env->CallIntMethod(eyerMediaCodec, jmethodId, index, render);
    }









    int EyerMediaCodec::flush()
    {
        JNIEnv *env = Eyer::EyerJNIEnvManager::AttachCurrentThread();

        jclass eyerMediaCodecClass = env->GetObjectClass(Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader);
        if (eyerMediaCodecClass == nullptr) {
            EyerLog("MediaCodec Thread: Find EyerMediaCodec Class Fail\n");
        }

        jmethodID jmethodId = env->GetMethodID(eyerMediaCodecClass, "flush", "()I");
        if(jmethodId == nullptr){
            EyerLog("MediaCodec GetMethodID Fail\n");
        }

        env->DeleteLocalRef(eyerMediaCodecClass);

        return env->CallIntMethod(eyerMediaCodec, jmethodId);
    }


}