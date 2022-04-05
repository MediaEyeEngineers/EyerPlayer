#include "IOReadThread.hpp"

#include "AVDecodeQueueBox.hpp"

namespace Eyer
{
    IOReadThread::IOReadThread(EyerPlayerContext * _playerContext)
        : playerContext(_playerContext)
    {

    }

    IOReadThread::~IOReadThread()
    {

    }

    void IOReadThread::Run()
    {
        EyerLog("IOReadThread Start\n");
        EyerLog("URL: %s\n", playerContext->url.c_str());

        AVDecodeQueueBox decodeQueueBox;

        reader = new EyerAVReader(playerContext->url);
        int ret = reader->Open();
        if(ret){
            // 打开失败
        }
        else {
            // 打开成功
            int videoStreamIndex = reader->GetVideoStreamIndex();
            int audioStreamIndex = reader->GetAudioStreamIndex();

            decodeQueueBox.ClearAllStream();
            if(videoStreamIndex >= 0){
                EyerAVStream videoStream = reader->GetStream(videoStreamIndex);
                decodeQueueBox.AddStream(videoStream);
            }
            if(audioStreamIndex >= 0){
                EyerAVStream audioStream = reader->GetStream(audioStreamIndex);
                decodeQueueBox.AddStream(audioStream);
            }
            decodeQueueBox.StartAllDecoder();
        }

        while(1){
            if(stopFlag){
                break;
            }
        }

        decodeQueueBox.StopAllDecoder();

        if(reader != nullptr){
            reader->Close();
            delete reader;
            reader = nullptr;
        }

        EyerLog("IOReadThread End\n");
    }
}