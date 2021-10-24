#include "EyerPlayerRenderThread.h"

#include <QAudioFormat>
#include <QAudioOutput>

#include <QDebug>

EyerPlayerRenderThread::EyerPlayerRenderThread(Eyer::EyerPlayer * _eyerPlayer)
    : eyerPlayer(_eyerPlayer)
{

}

EyerPlayerRenderThread::~EyerPlayerRenderThread()
{

}

void EyerPlayerRenderThread::run()
{
    Eyer::EyerObserverQueue<Eyer::EyerAVFrame *> * videoQueue = eyerPlayer->GetQueueBox()->GetVideoOutputQueue();
    Eyer::EyerObserverQueue<Eyer::EyerAVFrame *> * audioQueue = eyerPlayer->GetQueueBox()->GetAudioOutputQueue();

    QAudioFormat fmt;
    fmt.setSampleRate(48000);   //设置采样率
    fmt.setChannelCount(2);     //设置通道数
    fmt.setSampleSize(16);      //设置采样大小
    fmt.setCodec("audio/pcm");  //设置编码方式
    fmt.setByteOrder(QAudioFormat::LittleEndian); //设置字节序
    fmt.setSampleType(QAudioFormat::SignedInt); //设置样本数据类型
    QAudioOutput *out = new QAudioOutput(fmt);
    QIODevice *io = out->start();  //开始播放

    while(!stopFlag){
        std::unique_lock<std::mutex> lck(eyerPlayer->GetQueueBox()->cvBox.mtx);
        while(!stopFlag && videoQueue->SizeLock() <= 0 && audioQueue->SizeLock() <= 0){
            eyerPlayer->GetQueueBox()->cvBox.cv.wait(lck);
        }
        lck.unlock();

        videoQueue->Lock();
        int size = videoQueue->Size();
        if(size > 0){
            Eyer::EyerAVFrame * frame = videoQueue->FrontPop();
            emit RenderFrame(frame);
        }
        videoQueue->Unlock();

        audioQueue->Lock();
        size = audioQueue->Size();
        if(size > 0){
            Eyer::EyerAVFrame * frame = audioQueue->FrontPop();

            Eyer::EyerAVFrame outFrame;
            frame->Resample(outFrame, Eyer::EyerAVSampleFormat::SAMPLE_FMT_S16, 48000);

            qint64 audioLen = outFrame.GetLinesize(0);
            //qDebug() << "audioLen====" << audioLen << endl;
            //audioLen = 1024 * 2 * 2;
            //qDebug() << "audioLenxxxx" << audioLen << endl;
            char * data = (char *)outFrame.GetData(0);

            qint64 writedLen = 0;
            while(writedLen < audioLen){
                qint64 ret = io->write(data + writedLen, audioLen - writedLen);
                writedLen += ret;
            }

            if(frame != nullptr){
                delete frame;
                frame == nullptr;
            }
        }
        audioQueue->Unlock();
    }

    out->stop();
}

int EyerPlayerRenderThread::Stop()
{
    std::unique_lock<std::mutex> lck(eyerPlayer->GetQueueBox()->cvBox.mtx);
    stopFlag = 1;
    eyerPlayer->GetQueueBox()->cvBox.cv.notify_all();
    lck.unlock();

    this->quit();
    this->wait();

    return 0;
}
