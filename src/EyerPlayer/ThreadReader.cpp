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

        int videoStream = reader.GetVideoStreamIndex();
        EyerLog("Video Stream Index: %d\n", videoStream);

        int audioStream = reader.GetAudioStreamIndex();
        EyerLog("Audio Stream Index: %d\n", audioStream);

        ThreadDecode decoder;
        decoder.Start();
        // 该线程用于读取视频流
        while(!stopFlag) {

        }
        decoder.Stop();
        EyerLog("ThreadReader End\n");
    }
}