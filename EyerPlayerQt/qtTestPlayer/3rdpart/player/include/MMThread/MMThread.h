
#pragma once
#include<thread>
class MMThread {
public:
	~MMThread();
	virtual void run() = 0;
	int start();
	int stop();
	int stopFlag = 1;
	int setDecath();
private:
	std::thread *myThread = 0;
	
};



// TODO: 在此处引用程序需要的其他标头。
