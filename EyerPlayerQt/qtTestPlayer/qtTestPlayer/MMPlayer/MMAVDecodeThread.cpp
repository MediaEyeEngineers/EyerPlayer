#include "MMPlayer.h"
#include "MMAV/MMAV.h"

MMAVDecodeThread::MMAVDecodeThread(MMAVEnum mmavEnum){
    typeEnum = mmavEnum;
    decoder = new MMAVDecoder();
}

MMAVDecodeThread::~MMAVDecodeThread() {

    while (packetQueue.Size() != 0) {
        MMAVPacket* p = 0;
        packetQueue.Pop(&p);
        delete p;
        p = nullptr;

    }

    while (freamQueue.Size() != 0) {
        MMAVFream* p = 0;
        freamQueue.Pop(&p);
        delete p;
        p = nullptr;
    }
    //printf("packetQueue.Size()=%d,freamQueue.Size()=%d\n", packetQueue.Size(), freamQueue.Size());
}


int MMAVDecodeThread::init(MMAVStream* avStream) {
    return decoder->init(avStream);
}

int MMAVDecodeThread::putPacket(MMAVPacket* packet) {
    packetQueue.Push(packet);
    return 0;
}

int MMAVDecodeThread::getPacketQueueSize() {
    return packetQueue.Size();
}

int MMAVDecodeThread::getFreamQueueSize() {
    return freamQueue.Size();
}

int MMAVDecodeThread::popFreamFromQueue(MMAVFream** f) {
     int ret = freamQueue.Pop(f);
     return ret;
}

void MMAVDecodeThread::setBaseTime(int ben, int num) {
    timeBaseDen = ben;
    timeBaseNum = num;
}



void MMAVDecodeThread::run() {
    // 解码操作
    int freamCount = 0;
    while (stopFlag) {
        if (typeEnum == MMAVEnum::MMAV_AUDIO_TYPE) {
            // printf("decoder audio Thread is run\n");
        }
        else if (typeEnum == MMAVEnum::MMAV_VIDEO_TYPE) {
            // printf("decoder video Thread is run\n");
        }

        // 当解码线程的 packetQueue中 packet数量为0 则使当前线程睡眠1ms
        if (packetQueue.Size() == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        MMAVPacket* pkt = nullptr;

        int ret = packetQueue.Pop(&pkt);

        if (ret) {
            // 队列为空，取不到 Packet
            break;
        }

        decoder->sendPacket(pkt);


        while (1 && stopFlag) {

            if (freamQueue.Size() > 10) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }

            MMAVFream* fream = new MMAVFream;
            ret = decoder->receiveFream(fream);



            if (ret) {
                delete fream;
                fream = NULL;
                break;
            }

            freamQueue.Push(fream);
            if (typeEnum == MMAVEnum::MMAV_VIDEO_TYPE) {
                //printf("freamQueue.Size()=%d,FreamTime=%lld,Decoder Video  Success\n", freamQueue.Size(),fream->getFreamTime());
            }

            else if (typeEnum == MMAVEnum::MMAV_AUDIO_TYPE) {
                //printf("FreamTime=%f,Decoder Audio  Success\n", 1.0 * fream->getFreamTime()*timeBaseNum/timeBaseDen);
            }

        }

        delete pkt;
        pkt = nullptr;
    }

    if (typeEnum == MMAVEnum::MMAV_VIDEO_TYPE) {
        printf("Decoder Video Over================\n");
    }
    else if (typeEnum == MMAVEnum::MMAV_AUDIO_TYPE) {
        printf("Decoder Audio Over================\n");
    }
    stopFlag = 0;
}
