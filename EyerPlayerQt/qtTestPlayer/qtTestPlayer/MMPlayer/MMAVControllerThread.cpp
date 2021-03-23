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

    // ����Ƶ����Ƶ֡����˳ʱ����
    MMAVFream* videoFream = 0;
    MMAVFream* audioFream = 0;

    // ��ȡ�߳�����ʱ���ʱ��

    long long startTime = MMAVTime::getTime();
    long long allPauseTime = 0;
    while (stopFlag) {
        // long long t1 = MMAVTime::getTime();
        // printf("time = %d\n", MMAVTime::getTime() - startTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        // std::cout<<std::endl;
        // ��ȡ����֡��ʱ��

        long long nowTime = MMAVTime::getTime();

        // �û��������ͣ  ����ѭ�� ʹ��ǰ�߳�����

        while(playState == VideoState::VIDEO_PAUSE_STATE) {
            // printf("controller Thread is pause!%d\n", playState);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // ��ͣ�˶೤ʱ��
        allPauseTime += MMAVTime::getTime() - nowTime;
        // ��Ƶ��֡��ʼ����0��ʼ  ���Լ�ȥ��ǰ�߳�������ʱ��


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
                // printf("��Ƶ֡: ����ʱ��=%lld(ms), ��Ƶʱ��=%f(ms), ��Ƶ֡ʱ�� = %lld(ms)\n", dTime, ftime, fream->getFreamTime());


                // fream���������ɾ��
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
                // printf("��Ƶ֡: ����ʱ��=%lld(ms), ��Ƶʱ��=%f(ms), ��Ƶ֡ʱ�� = %lld(ms)\n", dTime, ftime2, fream2->getFreamTime());
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
