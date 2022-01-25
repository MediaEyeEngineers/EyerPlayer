#include "ThreadPlayCtr.hpp"

#include "EyerCore/EyerCore.hpp"

#include "EyerDecodeQueue/EyerDecodeQueueHeader.hpp"

#include "ThreadEventLoop.hpp"
#include "ThreadAudioPlay.hpp"

namespace Eyer
{
    ThreadPlayCtr::ThreadPlayCtr(DecoderBox * _decoderBox, ThreadEventLoop * _eventLoop)
        : eventLoop(_eventLoop)
        , decoderBox(_decoderBox)
    {

    }

    ThreadPlayCtr::~ThreadPlayCtr()
    {

    }

    void ThreadPlayCtr::Run()
    {
        EyerLog("ThreadPlayCtr Start\n");
        // 该线程用于控制视频流

        int videoStreamIndex = decoderBox->GetVideoStreamIndex();
        int audioStreamIndex = decoderBox->GetAudioStreamIndex();

        EyerLog("Play Ctr video stream index: %d\n", videoStreamIndex);
        EyerLog("Play Ctr audio stream index: %d\n", audioStreamIndex);

        if(videoStreamIndex < 0 && audioStreamIndex < 0){
            EyerLog("No Video, No Audio\n");
        }

        if(audioStreamIndex < 0){
            EyerLog("No Audio\n");
            // 应当采用外部时钟同步
        }

        if(videoStreamIndex < 0){
            EyerLog("No Video\n");
        }

        ThreadAudioPlay * audioPlayThread = new ThreadAudioPlay();
        audioPlayThread->Start();

        while(!stopFlag) {
            std::unique_lock<std::mutex> locker(decoderBox->cvBox.mtx);
            decoderBox->cvBox.cv.wait(locker);
        }

        if(audioPlayThread != nullptr){
            audioPlayThread->Stop();
            delete audioPlayThread;
            audioPlayThread = nullptr;
        }

        EyerLog("ThreadPlayCtr End\n");
    }

    int ThreadPlayCtr::SetStopFlag()
    {
        std::unique_lock<std::mutex> locker(decoderBox->cvBox.mtx);
        stopFlag = 1;
        decoderBox->cvBox.cv.notify_all();
        return 0;
    }

    int ThreadPlayCtr::SetStartEventLoopFlag()
    {
        std::unique_lock<std::mutex> locker(decoderBox->cvBox.mtx);
        eventLoopFlag = 1;
        decoderBox->cvBox.cv.notify_all();
        return 0;
    }
}