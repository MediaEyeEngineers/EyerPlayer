#include "MMPlayer.h"
#include "MMAV/MMAV.h"
#include "MMPlayOpenGL/MMPlayOpenGL.h"


MMAVControllerThread::MMAVControllerThread(std::string path, int startPlayTime):path(path),startPlayTime(startPlayTime) {

}

MMAVControllerThread::~MMAVControllerThread(){

}

int MMAVControllerThread::pauseVideo() {
    playState = VideoState::VIDEO_PAUSE_STATE;
    return 0;
}

int MMAVControllerThread::playVideo() {
    playState = VideoState::VIDEO_PLAY_STATE;
    return 0;
}

void MMAVControllerThread::run(){



    MMAVDecodeThread* videoThread =  new MMAVDecodeThread(MMAVEnum::MMAV_VIDEO_TYPE);

    MMAVDecodeThread* audioThread =  new MMAVDecodeThread(MMAVEnum::MMAV_AUDIO_TYPE);

    if (readerThread == nullptr) {
        readerThread = new MMAVReaderThread(path, startPlayTime, videoThread, audioThread);
    }

    readerThread->start();

    // 对视频和音频帧进行顺时播放
    MMAVFream* videoFream = 0;
    MMAVFream* audioFream = 0;

    // 获取线程启动时候的时间

    long long startTime = MMAVTime::getTime();
    long long allPauseTime = 0;
    while (stopFlag) {
        // long long t1 = MMAVTime::getTime();
        // printf("time = %d\n", MMAVTime::getTime() - startTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        // std::cout<<std::endl;
        // 读取到这帧的时间

        long long nowTime = MMAVTime::getTime();

        // 用户点击了暂停  进入循环 使当前线程自旋

        while(playState == VideoState::VIDEO_PAUSE_STATE) {
            // printf("controller Thread is pause!%d\n", playState);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // 暂停了多长时间
        allPauseTime += MMAVTime::getTime() - nowTime;
        // 视频的帧开始是以0开始  所以减去当前线程启动的时间


        if (videoFream == nullptr) {
            videoThread->popFreamFromQueue(&videoFream);
        }

        if (videoFream != nullptr) {
            // video
            int dTime = MMAVTime::getTime() - startTime - allPauseTime;
            double ftime = (1.0 * videoFream->getFreamTime() * videoThread->timeBaseNum / videoThread->timeBaseDen) * 1000.0;
            ftime -= startPlayTime * 100.0;
            //ftime = 0;
            if (dTime >= ftime) {

                freamQueue.Push(videoFream);


                // fream->PrintFream();
                // printf("video: playTime=%lld, fream->getFreamTime() => %lld, ftime = %f\n", dTime, fream->getFreamTime(), ftime);
                // printf("视频帧: 播放时间=%lld(ms), 视频时间=%f(ms), 视频帧时间 = %lld(ms)\n", dTime, ftime, fream->getFreamTime());


                // fream不在这进行删除
                videoFream = nullptr;
                //delete fream;
                //fream = nullptr;

            }
        }




        if (audioFream == nullptr) {
            audioThread->popFreamFromQueue(&audioFream);
        }

        if (audioFream != nullptr) {
            // audio
            int dTime = MMAVTime::getTime() - startTime - allPauseTime;
            double ftime2 = (1.0 * audioFream->getFreamTime() * audioThread->timeBaseNum / audioThread->timeBaseDen) * 1000;
            ftime2 -= startPlayTime * 1000.0;
            if (dTime >= ftime2) {
                // printf("audio: playTime=%lld, fream2->getFreamTime() => %lld, ftime = %f\n", dTime, fream2->getFreamTime(), ftime2);
                // printf("音频帧: 播放时间=%lld(ms), 音频时间=%f(ms), 音频帧时间 = %lld(ms)\n", dTime, ftime2, fream2->getFreamTime());
                delete audioFream;
                audioFream = nullptr;
            }
        }
        if (readerThread->stopFlag == 0 && videoThread->stopFlag == 0 && audioThread->stopFlag == 0) {
            readerThread->stop();
            videoThread->stop();
            audioThread->stop();
            break;
        }
        // printf("fream ==>> %d\n", MMAVTime::getTime() - t1); // 0

    }

    if (readerThread->stopFlag == 1) {
        readerThread->stop();
    }
    if (videoThread->stopFlag == 1) {
        videoThread->stop();
    }
    if (audioThread->stopFlag == 1) {
        audioThread->stop();
    }
    delete readerThread, videoThread, audioThread;
    readerThread = 0;
    videoThread = 0;
    audioThread = 0;
    std::cout << ("controller is stop \n") << std::endl;
    stopFlag = 0;
}
