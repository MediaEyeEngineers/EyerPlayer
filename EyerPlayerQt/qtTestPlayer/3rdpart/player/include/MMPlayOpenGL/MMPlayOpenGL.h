#pragma once
#include "MMThread/MMThread.h"
#include "MMAV/MMAV.h"
#include "MMAVQueue/MMAVQueue.h"

class MMOpenGLThread :public MMThread {
public:
	MMOpenGLThread();
	~MMOpenGLThread();
	virtual void run();
	int putFream(MMAVFream* f);

public:
	MMQueue<MMAVFream> freamQueue;
private:


};

