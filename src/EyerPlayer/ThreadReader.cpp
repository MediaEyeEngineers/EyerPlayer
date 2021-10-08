#include "ThreadReader.hpp"

#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

#include "ThreadDecode.hpp"

namespace Eyer
{
    void ThreadReader::Run()
    {
        EyerLog("ThreadReader Start\n");

        Eyer::EyerAVReader reader("/Users/miaoyuqiao/Desktop/HDR/1080_1920_HDR_Color_Card.mp4");
        int ret = reader.Open();
        if(ret){
            // 打开失败
        }

        int streamCount = reader.GetStreamCount();
        EyerLog("Stream Count: %d\n", streamCount);

        int videoStreamIndex = reader.GetVideoStreamIndex();
        EyerLog("Video Stream Index: %d\n", videoStreamIndex);

        int audioStreamIndex = reader.GetAudioStreamIndex();
        EyerLog("Audio Stream Index: %d\n", audioStreamIndex);


        EyerAVStream videoStream = reader.GetStream(videoStreamIndex);
        Eyer::EyerObserverQueue<EyerAVPacket *> queueVideoPacket;
        ThreadDecode videoDecoderThread(videoStream, &queueVideoPacket);
        videoDecoderThread.Start();

        EyerAVStream audioStream = reader.GetStream(audioStreamIndex);
        Eyer::EyerObserverQueue<EyerAVPacket *> queueAideoPacket;
        ThreadDecode audioDecoderThread(audioStream, &queueAideoPacket);
        audioDecoderThread.Start();

        // 该线程用于读取视频流
        while(!stopFlag) {
            EyerAVPacket * packet = new EyerAVPacket();
            int ret = reader.Read(*packet);
            if(ret){
                // 读取失败或者网络出错
                if(packet != nullptr){
                    delete packet;
                    packet = nullptr;
                }
                break;
            }

            // EyerLog("pts: %lld\n", packet->GetPTS());
            if(packet->GetStreamIndex() == videoStreamIndex){
                queueVideoPacket.Push(packet);
            }
            else if(packet->GetStreamIndex() == audioStreamIndex){
                queueAideoPacket.Push(packet);
            }
            else {
                if(packet != nullptr){
                    delete packet;
                    packet = nullptr;
                }
            }
        }

        videoDecoderThread.Stop();
        audioDecoderThread.Stop();

        EyerLog("ThreadReader End\n");
    }
}