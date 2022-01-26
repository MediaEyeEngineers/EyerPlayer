#include "ThreadAndroidAudioPlay.hpp"

#include "EyerJNI/EyerJNIHeader.hpp"

namespace Eyer
{
    void ThreadAndroidAudioPlay::Run()
    {
        EyerLog("ThreadAndroidAudioPlay Start\n");

        // 初始化音频播放
        EyerJNIEnv jniEnv = EyerJNIEnvManager::AttachCurrentThread();

        int sampleRate = 48000;
        EyerJNIObject * audioTrack = new EyerJNIObject(&jniEnv, "com/zzsin/eyerplayer/audio/EyerAudioTrack", "(I)V", sampleRate);

        audioTrack->CallVoid("play", "()V");

        EyerAVFrame * audioFrame = nullptr;
        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);
            audioFrame = GetAudioFrame();
            // EyerLog("Render Audio\n");

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