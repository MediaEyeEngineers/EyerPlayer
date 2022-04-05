#include "AVDecodeQueueBox.hpp"

#include "EyerDecodeQueue/EyerDecodeQueueHeader.hpp"

namespace Eyer
{
    AVDecodeQueueBox::AVDecodeQueueBox()
    {

    }

    AVDecodeQueueBox::~AVDecodeQueueBox()
    {
        ClearAllStream();
        StopAllDecoder();
    }

    int AVDecodeQueueBox::AddStream(const EyerAVStream & stream)
    {
        streamList.push_back(stream);
        return 0;
    }

    int AVDecodeQueueBox::ClearAllStream()
    {
        streamList.clear();
        return 0;
    }

    int AVDecodeQueueBox::StartAllDecoder()
    {
        for(int i=0;i<streamList.size();i++){
            const EyerAVStream & stream = streamList[i];

            EyerDecodeQueueFFmpeg * decodeQueue = new EyerDecodeQueueFFmpeg(stream);
            decodeQueue->StartDecoder();

            decoderList.push_back(decodeQueue);
        }
        return 0;
    }

    int AVDecodeQueueBox::StopAllDecoder()
    {
        for(int i=0;i<decoderList.size();i++){
            EyerDecodeQueueBase * decodeQueue = decoderList[i];
            if(decodeQueue != nullptr){
                decodeQueue->StopDeocder();
                delete decodeQueue;
                decodeQueue = nullptr;
            }
        }
        decoderList.clear();
        return 0;
    }
}