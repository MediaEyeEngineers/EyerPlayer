#include <thread>
#include "MMThread.h"

MMThread::~MMThread(){
	if (myThread != nullptr) {
		// 当 当前的任务完成后 回收线程
		delete myThread;
		myThread = nullptr;
	}
}


int MMThread::start(){
	
	if (myThread == nullptr) {
		stopFlag = 1;
		myThread = new std::thread(&MMThread::run, this);
	}


	//std::thread myThread(&MMThread::run,this);
	//myThread.detach();
	// 当任务执行完成后删除回收线程
	return 0;
}

int MMThread::stop() {
	// 暂停回收线程 
	if (myThread != nullptr) {
		stopFlag = 0;
		// 把当前的任务挂起 阻塞住主线程 如果完成当前这个线程任务
		myThread->join();

		// 当 当前的任务完成后 回收线程
		delete myThread;
		myThread = nullptr;
	}
	return 0;
}


int MMThread::setDecath() {
	if (myThread != nullptr) {
		myThread->detach();
	}
	return 0;
}