#pragma once


#include <iostream>
#include <string>
#include "MMThread/MMThread.h"
#include "MMAV/MMAV.h"
#include "MMAVQueue/MMAVQueue.h"

// 帧类型枚举
enum MMAVEnum
{
	MMAV_VIDEO_TYPE = 0,
	MMAV_AUDIO_TYPE = 1,
};

// 视频播放状态
enum VideoState {
	VIDEO_PAUSE_STATE = 0,
	VIDEO_PLAY_STATE = 1,

};

class MMAVReaderThread;
class MMAVDecodeThread;
class MMAVFrameQueue;

// 
class MMAVFrameQueue {
public:
	MMAVFrameQueue();
	~MMAVFrameQueue();

public:
	MMQueue<MMAVFream> freamQueue;
};

// 播放器控制线程
class MMAVControllerThread : public MMThread {
public:
	MMAVControllerThread(std::string path, int startPlayTime);
	~MMAVControllerThread();
	void run();
	int pauseVideo();
	int playVideo();

public:
	MMQueue<MMAVFream> freamQueue;

private:
	int startPlayTime;
	std::string path;
	MMAVReaderThread* readerThread = 0;
	VideoState playState = VideoState::VIDEO_PLAY_STATE;

};


// 读流线程
class MMAVReaderThread : public MMThread {
public:
	MMAVReaderThread(std::string path, int startPlayTime, MMAVDecodeThread* decoderVideoThread, MMAVDecodeThread* decoderAudioThread);
	~MMAVReaderThread();
	void run();

private:
	int startPlayTime;
	std::string path;
	MMAVDecodeThread* decoderVideoThread = 0;
	MMAVDecodeThread* decoderAudioThread = 0;
};


// 解码线程
class MMAVDecodeThread : public MMThread {
public:
	MMAVDecodeThread(MMAVEnum mmavEnum);
	~MMAVDecodeThread();
	virtual void run();

	int init(MMAVStream* AVStream);
	int putPacket(MMAVPacket *packet);
	int getPacketQueueSize();

	int getFreamQueueSize();
	int popFreamFromQueue(MMAVFream** f);

	void setBaseTime(int ben , int num);

public:
	int timeBaseDen;
	int timeBaseNum;

private:

	MMAVDecoder *decoder = 0;

	MMQueue<MMAVPacket> packetQueue;
	MMQueue<MMAVFream> freamQueue;

	MMAVEnum typeEnum;
};


class MMPlayer {
public:

	MMPlayer(std::string path);

	~MMPlayer();
	

	// 对视频操作
	// 打开视频
	int open();

	// 关闭视频
	int close();

	// 暂停
	int pause();

	// 播放
	int play();

	// 跳转(进度条功能) 单位s
	int seek(int t);

private:
	std::string path;
	MMAVControllerThread* controllerThread = 0;
};


