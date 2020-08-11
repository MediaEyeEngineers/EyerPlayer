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
        EyerLog("AVDecoder MediaCodec Thread Start\n");

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

        jobject eyerMediaCodec = env->NewObject(eyerMediaCodecClass, eyerMediaCodecMethod);
        if(eyerMediaCodec == nullptr){
            EyerLog("MediaCodec Thread: EyerMediaCodec Class Fail\n");
        }



        // 调用 Init 函数
        jmethodID eyerMediaCodecMethod_Init = env->GetMethodID(eyerMediaCodecClass, "init", "(II)I");
        if(eyerMediaCodecMethod_Init == nullptr){
            EyerLog("MediaCodec Thread: Init GetMethodID Fail\n");
        }

        int ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Init, stream.GetWidth(), stream.GetHeight());
        EyerLog("MediaCodec Thread: MediaCodec init: %d\n", ret);



        AVFrameQueue * frameQueue = nullptr;
        if (stream.GetStreamType() == Eyer::EyerAVStreamType::STREAM_TYPE_VIDEO) {
            EyerLog("AVDecoder MediaCodec Thread Start Video\n");
            frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_VIDEO, &frameQueue);
        } else if (stream.GetStreamType() == Eyer::EyerAVStreamType::STREAM_TYPE_AUDIO) {
            EyerLog("AVDecoder MediaCodec Thread Start Audio\n");
            frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_DECODER_AUDIO, &frameQueue);
        }

        Eyer::EyerAVRational timebase = stream.timebase;


        Eyer::EyerAVBitstreamFilter bitstreamFilter;

        // 解码
        while (!stopFlag) {
            if (frameQueue != nullptr) {
                if (frameQueue->Size() > 10) {
                    continue;
                }
            }


            Eyer::EyerAVPacket * pkt = nullptr;
            pktQueue.FrontPop(&pkt);
            if (pkt == nullptr) {
                continue;
            }

            if(pkt->IsLast()){
                if (pkt != nullptr) {
                    delete pkt;
                    pkt = nullptr;
                }
                break;
            }

            cacheSize -= pkt->GetSize();

            unsigned char * dstData = nullptr;
            int dstLen = 0;
            bitstreamFilter.Filter(stream, pkt, &dstData, &dstLen);

            if(dstData != nullptr){
                free(dstData);
                dstData = nullptr;
            }

            if (pkt != nullptr) {
                delete pkt;
                pkt = nullptr;
            }
        }

        // 调用 Uninit 函数
        jmethodID eyerMediaCodecMethod_Uninit = env->GetMethodID(eyerMediaCodecClass, "uninit", "()I");
        if(eyerMediaCodecMethod_Uninit == nullptr){
            EyerLog("MediaCodec Thread: Init GetMethodID Fail\n");
        }

        ret = env->CallIntMethod(eyerMediaCodec, eyerMediaCodecMethod_Uninit);
        EyerLog("MediaCodec Thread: MediaCodec uninit: %d\n", ret);

        EyerLog("AVDecoder MediaCodec Thread Stop\n");
    }
}