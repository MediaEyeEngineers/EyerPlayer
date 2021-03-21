#include "MMPlayer.h"
#include "MMAV/MMAV.h"
#include <string>

MMAVReaderThread::MMAVReaderThread(std::string path, int startPlayTime, MMAVDecodeThread* decoderVideoThread, MMAVDecodeThread* decoderAudioThread){
	this->path = path;
	this->startPlayTime = startPlayTime;
	this->decoderVideoThread = decoderVideoThread;
	this->decoderAudioThread = decoderAudioThread;
}

MMAVReaderThread::~MMAVReaderThread() {
	if (decoderVideoThread != nullptr) {
		delete decoderVideoThread;
		decoderVideoThread = nullptr;
	}
	if (decoderAudioThread != nullptr) {
		delete decoderAudioThread;
		decoderAudioThread = nullptr;
	}
}


void MMAVReaderThread::run() {
	MMAVReader reader;
	
	int ret = reader.open(path.c_str(), startPlayTime);
	
	if (ret != 0) {
		printf("open file fail\n");
		// 文件打开失败
		return;
	}

	// 视频和音频流下标
	int videoIndex = reader.getVideo();
	int audioIndex = reader.getAudio();

	MMAVStream videoStream;
	ret = reader.getStream(&videoStream, videoIndex);
	videoStream.test(1);
	decoderVideoThread->setBaseTime(videoStream.timeBaseDen, videoStream.timeBaseNum);
	//printf("%d,%d\n",decoderVideoThread->timeBaseDen, decoderVideoThread->timeBaseDen);
	if (ret < 0) {
		printf("getStream fail\n");
	}

	MMAVStream audioStream;
	ret = reader.getStream(&audioStream, audioIndex);
	audioStream.test(2);
	decoderAudioThread->setBaseTime(audioStream.timeBaseDen, audioStream.timeBaseNum);
	if (ret < 0) {
		printf("getStream fail\n");
	}


	

	// 初始化解码器  
	// 分别创建新的线程来对视频和音频解码
	// 如果用这个读流线程 也进行解码操作的话  首先流获取太慢 则会影响解码的速度
	ret = decoderVideoThread->init(&videoStream);
	

	if (ret != 0) {

	}

	ret = decoderAudioThread->init(&audioStream);
	if (ret != 0) {

	}


	// 读流 和 解码

	decoderVideoThread->start();

	decoderAudioThread->start();
	
	// 如果播放到一半时候  用户使用暂停 那么执行当前线程的stop()  把当前线程join
	// 1. 如果是while(1) 那么就会选择把后面的流读取完 后暂停
	// 2. 使用一个信号值stopFlag  来判断当前线程是否进行暂停
	while (stopFlag) {

		// 如果解码的队列中packet大于5个  则使当前这个线程自旋
		if (decoderVideoThread->getPacketQueueSize() > 5 && decoderAudioThread->getPacketQueueSize() > 5) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}

		MMAVPacket* pkt = new MMAVPacket();

		// 读packet  判断是否是最后一个packet
		int ret = reader.read(pkt);

		if (ret) {
			// printf("put packet over or fail \n");
			delete pkt;
			pkt = nullptr;
			break;
		}

		
		if (pkt->getStreamIndex() == videoIndex) {
			// printf("put video stream packet!\n");
			decoderVideoThread->putPacket(pkt);
		}

		if (pkt->getStreamIndex() == audioIndex) {
			// printf("put audio stream packet!\n");
			decoderAudioThread->putPacket(pkt);
		}

		//printf("put packet success \n");


	}
	while (1 && stopFlag) {
		if (decoderVideoThread->getPacketQueueSize() == 0 && decoderAudioThread->getPacketQueueSize() == 0) {
			decoderVideoThread->stop();
			decoderAudioThread->stop();
			break;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
	printf("reader.read packet over!!! \n");
	// 1.当 当前的线程读完packet后发现没有新的packet时候 packet线程自动回收 
	// 2.当 外部通知停止了读流线程后再停止以下的线程
	
}
