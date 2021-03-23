#include "MMPlayer.h"
#include "MMAV/MMAV.h"
#include <string>


MMPlayer::MMPlayer(std::string path){
	this->path = path;
	controllerThread = nullptr;
}

MMPlayer::~MMPlayer() {
	if (controllerThread != NULL) {
		delete controllerThread;
		controllerThread = nullptr;
	}
}


// 对视频操作
// 打开视频   使用线程对视频进行打开操作
int MMPlayer::open() {

	if (controllerThread == nullptr) {
		controllerThread = new MMAVControllerThread(path, 0);
		controllerThread->start();
	}
	return 0;
}

// 关闭视频
int MMPlayer::close() {

	if (controllerThread != NULL) {
		// 处于活跃线程 先暂停
        controllerThread->stop();
		delete controllerThread;
		controllerThread = nullptr;
	}
	return 0;
}

// 视频暂停
int MMPlayer::pause() {
	if (controllerThread != nullptr) {
		controllerThread->pauseVideo();
	}
	return 0;
}

// 播放
int MMPlayer::play() {
	if (controllerThread != nullptr) {
		controllerThread->playVideo();
	}
	return 0;
}

// 进度条  跳转到多少秒
int MMPlayer::seek(int t) {
	close();
	if (controllerThread == nullptr) {
		controllerThread = new MMAVControllerThread(path,20);
		controllerThread->start();
	}
	return 0;
}
