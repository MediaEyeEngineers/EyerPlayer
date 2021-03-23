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
    // printf("~MMAVReaderThread\n");
    // ��������ɾ��
    //if (decoderVideoThread != nullptr) {
    //	delete decoderVideoThread;
    //	decoderVideoThread = nullptr;
    //}

    //if (decoderAudioThread != nullptr) {
    //	delete decoderAudioThread;
    //	decoderAudioThread = nullptr;
    //}
}


void MMAVReaderThread::run() {
    MMAVReader reader;

    int ret = reader.open(path.c_str(), startPlayTime);

    if (ret != 0) {
        printf("open file fail\n");
        // �ļ���ʧ��
        return;
    }

    // ��Ƶ����Ƶ���±�
    int videoIndex = reader.getVideo();
    int audioIndex = reader.getAudio();

    MMAVStream videoStream;
    ret = reader.getStream(&videoStream, videoIndex);
    //videoStream.test(1);
    decoderVideoThread->setBaseTime(videoStream.timeBaseDen, videoStream.timeBaseNum);
    //printf("%d,%d\n",decoderVideoThread->timeBaseDen, decoderVideoThread->timeBaseDen);
    if (ret < 0) {
        printf("getStream fail\n");
    }

    MMAVStream audioStream;
    ret = reader.getStream(&audioStream, audioIndex);
    //audioStream.test(2);
    decoderAudioThread->setBaseTime(audioStream.timeBaseDen, audioStream.timeBaseNum);
    if (ret < 0) {
        printf("getStream fail\n");
    }




    // ��ʼ��������
    // �ֱ𴴽��µ��߳�������Ƶ����Ƶ����
    // �������������߳� Ҳ���н�������Ļ�  ��������ȡ̫�� ���Ӱ�������ٶ�
    ret = decoderVideoThread->init(&videoStream);


    if (ret != 0) {

    }

    ret = decoderAudioThread->init(&audioStream);
    if (ret != 0) {

    }


    // ���� �� ����

    decoderVideoThread->start();

    decoderAudioThread->start();

    // ������ŵ�һ��ʱ��  �û�ʹ����ͣ ��ôִ�е�ǰ�̵߳�stop()  �ѵ�ǰ�߳�join
    // 1. �����while(1) ��ô�ͻ�ѡ��Ѻ��������ȡ�� ����ͣ
    // 2. ʹ��һ���ź�ֵstopFlag  ���жϵ�ǰ�߳��Ƿ������ͣ
    while (stopFlag) {

        // �������Ķ�����packet����5��  ��ʹ��ǰ����߳�����
        if (decoderVideoThread->getPacketQueueSize() > 5 && decoderAudioThread->getPacketQueueSize() > 5) {
            // printf("decoderVideoThread->getPacketQueueSize()=%d && decoderAudioThread->getPacketQueueSize()=%d \n", decoderVideoThread->getPacketQueueSize(), decoderAudioThread->getPacketQueueSize());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }

        MMAVPacket* pkt = new MMAVPacket();

        // ��packet  �ж��Ƿ������һ��packet
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
    }

    //while (1 && stopFlag) {
    //	if (decoderVideoThread->getPacketQueueSize() == 0 && decoderAudioThread->getPacketQueueSize() == 0) {
    //		decoderVideoThread->stop();
    //		decoderAudioThread->stop();
    //		break;
    //	}
    //	std::this_thread::sleep_for(std::chrono::microseconds(1));
    //}

    printf("reader packet over!!! \n");

    // 1.�� ��ǰ���̶߳���packet����û���µ�packetʱ�� packet�߳��Զ�����
    // 2.�� �ⲿֹ֪ͨͣ�˶����̺߳���ֹͣ���µ��߳�
    stopFlag = 0;
}
