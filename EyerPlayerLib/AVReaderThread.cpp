#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerPlayerEventManager.h"
#include "PlayerEvent.hpp"
#include <QDebug>

namespace EyerPlayer {
    AVReaderThread::AVReaderThread(Eyer::EyerString _url,Eyer::EyerEventQueue * _eventQueue, long long _openEventId,  AVFrameQueueManager * _queueManager, double _seekTime)
    {
        queueManager = _queueManager;
        url = _url;
        eventQueue = _eventQueue;
        openEventId = _openEventId;
        seekTime = _seekTime;
    }

    AVReaderThread::~AVReaderThread()
    {
        if(playerCtr != nullptr){
            playerCtr->Stop();
            delete playerCtr;
            playerCtr = nullptr;
        }
    }

    int AVReaderThread::Play()
    {
        if(playerCtr != nullptr){
            if(!playerCtr->IsRunning()){
                playerCtr->Detach();
            }
        }
        return 0;
    }

    int AVReaderThread::Pause()
    {
        if(playerCtr != nullptr){
            playerCtr->Stop();
        }
        return 0;
    }

    Eyer::EyerString AVReaderThread::GetURL()
    {
        return url;
    }

    void AVReaderThread::Run()
    {
        SetRunning();

        int recommendVideoIndex = 0;
        int recommendAudioIndex = 1;

        playerCtr = new PlayCtrThread(eventQueue, queueManager, recommendVideoIndex, recommendAudioIndex, seekTime);
        playerCtr->Detach();

        //// <===============Init Start===============>
        // Eyer::EyerAVQueue<Eyer::EyerAVPacket> pktQueue;
        int streamCount = 0;
        EventOpenResponse * event = nullptr;
        int isStop = 0;
        MediaInfo mediaInfo;

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

        mediaInfo.duration = reader.GetDuration();

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

            mediaInfo.AddStreamInfo(streamInfo);

            if(stream.streamIndex == recommendVideoIndex){
                AVDecoderThread * avdecoder = new AVDecoderThread(stream, streamInfo, eventQueue, queueManager);
                avdecoder->Detach();

                decodeThreadList.push_back(avdecoder);
            }
            if(stream.streamIndex == recommendAudioIndex){
                AVDecoderThread * avdecoder = new AVDecoderThread(stream, streamInfo, eventQueue, queueManager);
                avdecoder->Detach();

                decodeThreadList.push_back(avdecoder);
            }
        }

        event = new EventOpenResponse();
        event->SetFrom(EventTag::EVENT_AVREADER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(openEventId);
        event->status = EventOpenStatus::OPEN_STATUS_SUCCESS;
        event->mediaInfo = mediaInfo;
        eventQueue->Push(event);

        //// Return Event
        //// <===============Init End===============>
        ///
        /*
        for(int i=0;i<streamCount;i++){
            reader.SeekFrame(i, seekTime);
        }
        */

        reader.SeekFrame(recommendVideoIndex, seekTime);

        while(!stopFlag){
            isStop = 1;
            Eyer::EyerTime::EyerSleep(1000);

            int isRead = 0;
            for(int i=0;i<decodeThreadList.size();i++){
                AVDecoderThread * avdecoder = decodeThreadList[i];
                if(avdecoder->GetQueueSize() <= 10){
                    isRead = 1;
                }
            }

            if(isRead){
                Eyer::EyerAVPacket * pkt = new Eyer::EyerAVPacket();
                ret = reader.Read(pkt);
                if(ret){
                    delete pkt;
                    isStop = 0;
                    goto END;
                }

                for(int i=0;i<decodeThreadList.size();i++){
                    AVDecoderThread * avdecoder = decodeThreadList[i];
                    avdecoder->PushPkt(pkt);
                }
            }
        }

END:
        if(!isStop){
            // 提示读取完成
            // qDebug() << "Wait for decoder thread end" << endl;
            for(int i=0;i<decodeThreadList.size();i++){
                AVDecoderThread * avdecoder = decodeThreadList[i];
                avdecoder->SetReadFinishFlag();
            }

            // qDebug() << "Wait for decoder thread end ==" << endl;

            for(int i=0;i<decodeThreadList.size();i++){
                AVDecoderThread * avdecoder = decodeThreadList[i];
                while(!stopFlag){
                    Eyer::EyerTime::EyerSleep(1000);
                    if(!avdecoder->IsRunning()){
                        break;
                    }
                }
            }

            // qDebug() << "Wait for decoder thread end ====" << endl;
        }

        reader.Close();

        for(int i=0;i<decodeThreadList.size();i++){
            AVDecoderThread * avdecoder = decodeThreadList[i];
            avdecoder->Stop();
            delete avdecoder;
        }
        decodeThreadList.clear();

        if(playerCtr != nullptr){
            playerCtr->Stop();
            delete playerCtr;
            playerCtr = nullptr;
        }

        SetStoping();
    }
}
