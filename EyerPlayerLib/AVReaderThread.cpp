#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerPlayerEventManager.h"
#include "PlayerEvent.hpp"
#include <QDebug>

namespace EyerPlayer {
    AVReaderThread::AVReaderThread(Eyer::EyerString _url,Eyer::EyerEventQueue * _eventQueue, long long _openEventId,  AVFrameQueueManager * _queueManager)
    {
        queueManager = _queueManager;
        url = _url;
        eventQueue = _eventQueue;
        openEventId = _openEventId;
    }

    AVReaderThread::~AVReaderThread()
    {

    }

    void AVReaderThread::Run()
    {
        SetRunning();

        //// <===============Init Start===============>
        // Eyer::EyerAVQueue<Eyer::EyerAVPacket> pktQueue;
        int streamCount = 0;
        EventOpenResponse * event = nullptr;
        int isStop = 0;

        Eyer::EyerAVReader reader(url);
        int ret = reader.Open();

        if(ret){
            // Open Fail
            // Push Event Into Event Queue
            event = new EventOpenResponse();
            event->SetFrom(EventTag::EVENT_AVREADER);
            event->SetTo(EventTag::EVENT_MANAGER);
            event->SetRequestId(openEventId);
            event->status = EventOpenStatus::OPEN_STATUS_FAIL;
            eventQueue->Push(event);

            goto END;
        }

        streamCount = reader.GetStreamCount();

        for(int i=0;i<streamCount;i++){
            Eyer::EyerAVStream stream;
            reader.GetStream(stream, i);

            // 获取 Stream 信息
            StreamInfo streamInfo;
            if          (stream.GetStreamType() == Eyer::EyerAVStreamType::STREAM_TYPE_VIDEO){
                streamInfo.type = StreamType::STREAM_TYPE_VIDEO;
            }
            else if     (stream.GetStreamType() == Eyer::EyerAVStreamType::STREAM_TYPE_AUDIO){
                streamInfo.type = StreamType::STREAM_TYPE_AUDIO;
            }
            else        {
                streamInfo.type = StreamType::STREAM_TYPE_UNKNOW;
            }

            streamInfo.duration     = stream.GetDuration();
            streamInfo.width        = stream.GetWidth();
            streamInfo.height       = stream.GetHeight();

            Eyer::EyerAVRational streamTimebase;
            reader.GetStreamTimeBase(streamTimebase, i);
            streamInfo.timeBaseDen = streamTimebase.den;
            streamInfo.timeBaseNum = streamTimebase.num;


            // streamInfo.type

            AVDecoderThread * avdecoder = new AVDecoderThread(stream, streamInfo, eventQueue, queueManager);
            avdecoder->Detach();

            decodeThreadList.push_back(avdecoder);
        }

        event = new EventOpenResponse();
        event->SetFrom(EventTag::EVENT_AVREADER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(openEventId);
        event->status = EventOpenStatus::OPEN_STATUS_SUCCESS;
        eventQueue->Push(event);

        //// Return Event
        //// <===============Init End===============>

        for(int i=0;i<streamCount;i++){
            // reader.SeekFrame(i, 600.0);
        }

        while(!stopFlag){
            isStop = 1;
            Eyer::EyerTime::EyerSleep(1000);

            int isRead = 0;
            for(int i=0;i<decodeThreadList.size();i++){
                AVDecoderThread * avdecoder = decodeThreadList[i];
                if(avdecoder->GetQueueSize() <= 20){
                    isRead = 1;
                }
            }

            if(isRead){
                Eyer::EyerAVPacket * pkt = new Eyer::EyerAVPacket();
                ret = reader.Read(pkt);
                if(ret){
                    // Error
                    delete pkt;
                    isStop = 0;
                    goto END;
                }

                // pktQueue.Push(pkt);

                for(int i=0;i<decodeThreadList.size();i++){
                    AVDecoderThread * avdecoder = decodeThreadList[i];
                    avdecoder->PushPkt(pkt);
                }
            }
        }

END:
        if(!isStop){
            qDebug() << "Wait for clean" << endl;
            while(1){
                int cacheFrameCount = 0;
                for(int i=0;i<decodeThreadList.size();i++){
                    AVDecoderThread * avdecoder = decodeThreadList[i];
                    cacheFrameCount += avdecoder->GetFrameQueueSize();
                }
                if(cacheFrameCount <= 0){
                    break;
                }

                Eyer::EyerTime::EyerSleep(1000);
            }
        }

        reader.Close();

        for(int i=0;i<decodeThreadList.size();i++){
            AVDecoderThread * avdecoder = decodeThreadList[i];
            avdecoder->Stop();
            delete avdecoder;
        }
        decodeThreadList.clear();

        SetStoping();
    }
}
