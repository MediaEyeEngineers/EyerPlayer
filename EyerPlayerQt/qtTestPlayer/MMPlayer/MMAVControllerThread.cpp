#include "MMPlayer.h"
#include "MMAV/MMAV.h"
#include "MMPlayOpenGL/MMPlayOpenGL.h"

MMAVControllerThread::MMAVControllerThread(std::string path, int startPlayTime):path(path),startPlayTime(startPlayTime) {

}

MMAVControllerThread::~MMAVControllerThread(){
	while (freamQueue.Size() != 0) {
		MMAVFream* p = 0;
		freamQueue.Pop(&p);
		delete p;
		p = nullptr;
	}
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

	//openglThread->start();
	readerThread->start(); 
	
	// 对视频和音频帧进行顺时播放
	MMAVFream* fream = 0;
	MMAVFream* fream2 = 0;

	// 获取线程启动时候的时间
	long long startTime = MMAVTime::getTime();
	long long allPauseTime = 0;
	while (stopFlag) {

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
		long long dTime = MMAVTime::getTime() - startTime - allPauseTime;

		if (fream == nullptr) {
			videoThread->popFreamFromQueue(&fream);
		}
		if (fream2 == nullptr) {
			audioThread->popFreamFromQueue(&fream2);
		}
	
		if (fream == nullptr || fream2 == nullptr) {
			continue;
		}
		
		// video
		double ftime =( 1.0 * fream->getFreamTime() * videoThread->timeBaseNum / videoThread->timeBaseDen )* 1000;
		ftime -= startPlayTime * 1000.0;
		if (dTime >= ftime) {
            while (freamQueue.Size() >= 5) {
				continue;
			}
			freamQueue.Push(fream);
            std::cout << "playing :" <<1.0 * fream->getFreamTime()* videoThread->timeBaseNum / videoThread->timeBaseDen << std::endl;
			//fream->PrintFream();
			// printf("video: playTime=%lld, fream->getFreamTime() => %lld, ftime = %f\n", dTime, fream->getFreamTime(), ftime);
            // printf("视频帧: 播放时间=%lld(ms), 视频时间=%f(ms), 视频帧时间 = %lld(ms)\n", dTime, ftime, fream->getFreamTime());
			

			// fream不在这进行删除
			fream = nullptr;
			// delete fream;
			// fream = nullptr;
			
		}
		
		
	
		// audio
		double ftime2 = (1.0 * fream2->getFreamTime() * audioThread->timeBaseNum / audioThread->timeBaseDen) * 1000;
		ftime2 -= startPlayTime * 1000.0;
		if (dTime >= ftime2) {
			// printf("audio: playTime=%lld, fream2->getFreamTime() => %lld, ftime = %f\n", dTime, fream2->getFreamTime(), ftime2);
            // printf("音频帧: 播放时间=%lld(ms), 音频时间=%f(ms), 音频帧时间 = %lld(ms)\n", dTime, ftime2, fream2->getFreamTime());
			delete fream2;
			fream2 = nullptr;
		}
	
		
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

}
