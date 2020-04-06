#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "PlayerEvent.hpp"
#include <QDebug>


#include <QAudioFormat>
#include <QAudioOutput>

namespace EyerPlayer {
    AudioPlayThread::AudioPlayThread(Eyer::EyerEventQueue * _eventQueue, AVFrameQueueManager * _queueManager)
    {
        eventQueue = _eventQueue;
        queueManager = _queueManager;

        QAudioFormat fmt;
        fmt.setSampleRate(48000);
        fmt.setSampleSize(16);
        fmt.setChannelCount(2);
        fmt.setCodec("audio/pcm");
        fmt.setByteOrder(QAudioFormat::LittleEndian);
        fmt.setSampleType(QAudioFormat::SignedInt);

        QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
        if (!info.isFormatSupported(fmt)) {
            qDebug()<<"default format not supported try to use nearest";
            fmt = info.nearestFormat(fmt);
        }

        out = new QAudioOutput(fmt);
        // out->setBufferSize(48000);
        io = out->start();
    }

    AudioPlayThread::~AudioPlayThread()
    {
        if(out != nullptr){
            delete out;
            out = nullptr;
        }
    }

    void AudioPlayThread::Run()
    {
        SetRunning();

        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            AVFrameQueue * playerAudioFrameQueue = nullptr;
            queueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_AUDIO, &playerAudioFrameQueue);
            if(playerAudioFrameQueue == nullptr){
                continue;
            }

            Eyer::EyerAVFrame * f = nullptr;
            playerAudioFrameQueue->FrontPop(&f);
            if(f != nullptr){
                int len = f->GetAudioPackedData(nullptr);
                unsigned char * data = (unsigned char *)malloc(len);
                f->GetAudioPackedData(data);

                int alreadyWrited = 0;
                while(alreadyWrited < len){
                    int ret = io->write((char *)data + alreadyWrited, len - alreadyWrited);
                    alreadyWrited += ret;
                }

                free(data);

                delete f;
            }
            else{
                // qDebug() << "Get NULL" << endl;
            }
        }

        SetStoping();
    }
}
