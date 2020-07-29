#include "EyerPlayerThread.hpp"
#include "EyerAV/EyerAV.hpp"

#include "PlayerEvent.hpp"

namespace EyerPlayer {
    AVReaderThread::AVReaderThread(Eyer::EyerString _url, long long _openEventId, Eyer::EyerEventQueue * _eventQueue)
    {
        url = _url;
        openEventId = _openEventId;
        eventQueue = _eventQueue;
    }

    AVReaderThread::~AVReaderThread()
    {

    }

    void AVReaderThread::Run()
    {
        EyerLog("AVReader Thread Start\n");

        EventOpenResponse * event = nullptr;

        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);
            Eyer::EyerAVReader reader(url);
            int ret = reader.Open();

            if(ret){
                EyerLog("AVReader Thread Open Error: %d\n", ret);

                EventOpenResponse * event = new EventOpenResponse();
                event->SetFrom(EventTag::EVENT_AVREADER);
                event->SetTo(EventTag::EVENT_MANAGER);
                event->SetRequestId(openEventId);
                event->status = EventOpenStatus::OPEN_STATUS_FAIL;
                eventQueue->Push(event);

                break;
            }

            // 获取视频流编号
            int videoStreamIndex = reader.GetVideoStreamIndex();
            if(videoStreamIndex >= 0){
                // 创建视频解码线程
            }
            // 获取音频流编号
            int audioStreamIndex = reader.GetAudioStreamIndex();
            if(audioStreamIndex >= 0){
                // 创建音频解码线程
            }

            while(1){
                Eyer::EyerAVPacket * packet = new Eyer::EyerAVPacket();
                ret = reader.Read(packet);

                if(ret){
                    // 读取错误 或者 视频结束
                    goto END;
                }

                if(packet->GetStreamId() == videoStreamIndex){

                }
                if(packet->GetStreamId() == audioStreamIndex){

                }

                EyerLog("AVReader Thread: %lld\n", packet->GetPTS());

                delete packet;
            }
        }

    END:
        EyerLog("AVReader Thread Start\n");
    }
}
