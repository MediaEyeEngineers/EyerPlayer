#include "ThreadAndroidAudioPlay.hpp"

#include "EyerJNI/EyerJNIHeader.hpp"

namespace Eyer
{
    void ThreadAndroidAudioPlay::Run()
    {
        EyerLog("ThreadAndroidAudioPlay Start\n");

        // 初始化重采样
        EyerAVResample resample;
        resample.Init(
                EyerAVChannelLayout::EYER_AV_CH_LAYOUT_MONO,
                EyerAVSampleFormat::SAMPLE_FMT_S16,
                48000,

                EyerAVChannelLayout::EYER_AV_CH_LAYOUT_MONO,
                EyerAVSampleFormat::SAMPLE_FMT_FLTP,
                48000
        );

        // 初始化音频播放
        EyerJNIEnv jniEnv = EyerJNIEnvManager::AttachCurrentThread();

        int sampleRate = 48000;
        EyerJNIObject * audioTrack = new EyerJNIObject(&jniEnv, "com/zzsin/eyerplayer/audio/EyerAudioTrack", "(I)V", sampleRate);

        audioTrack->CallVoid("play", "()V");

        EyerAVFrame * audioFrame = nullptr;
        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);
            audioFrame = GetAudioFrame();

            // 上传数据
            EyerJNIByteArray pcmJavaData(&jniEnv, 10);

            if(audioFrame != nullptr){
                // EyerLog("Render Audio OK\n");
                delete audioFrame;
                audioFrame = nullptr;
            }
        }

        audioTrack->CallVoid("stop", "()V");

        if(audioTrack != nullptr){
            delete audioTrack;
            audioTrack = nullptr;
        }

        // 销毁音频播放
        EyerJNIEnvManager::DetachCurrentThread();

        EyerLog("ThreadAndroidAudioPlay End\n");
    }

    int ThreadAndroidAudioPlay::SetStopFlag()
    {
        stopFlag = 1;
        return 0;
    }
}