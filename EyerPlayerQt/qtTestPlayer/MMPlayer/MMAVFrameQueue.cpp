#include "MMPlayer.h"

MMAVFrameQueue::MMAVFrameQueue() {

}

MMAVFrameQueue::~MMAVFrameQueue() {
	while (freamQueue.Size() != 0) {
		MMAVFream* p = 0;
		freamQueue.Pop(&p);
		delete p;
		p = nullptr;
	}
}