#include "QueueBox.hpp"

namespace Eyer
{
    QueueBox::QueueBox()
    {

    }

    QueueBox::~QueueBox()
    {

    }

    int QueueBox::AddStream(const EyerAVStream & stream)
    {
        streamList.push_back(stream);
        return 0;
    }

    int QueueBox::StartDeocder()
    {
        for(int i=0; i<streamList.size(); i++){
            const EyerAVStream & stream = streamList[i];
            EyerDeocdeQueue * decoderQueue = new EyerDeocdeQueueFFmpeg(stream, &cvBox);
            decoderQueue->StartDecode();
            decoderQueueList.push_back(decoderQueue);
        }

        isStart = true;
        return 0;
    }

    int QueueBox::StopDecoder()
    {
        for(int i=0; i<decoderQueueList.size(); i++) {
            EyerDeocdeQueue * decoderQueue = decoderQueueList[i];
            decoderQueue->StopDecode();
            delete decoderQueue;
        }
        decoderQueueList.clear();

        isStart = false;
        return 0;
    }

    int QueueBox::GetPacketQueueCacheSize()
    {
        int size = 0;
        for(int i=0; i<decoderQueueList.size(); i++) {
            EyerDeocdeQueue * decoderQueue = decoderQueueList[i];
            size += decoderQueue->GetPacketCacheSize();
        }
        return size;
    }

    int QueueBox::PutPacket(EyerAVPacket * packet)
    {
        int streamIndex = packet->GetStreamIndex();
        for(int i=0; i<decoderQueueList.size(); i++){
            EyerDeocdeQueue * decoderQueue = decoderQueueList[i];
            if(decoderQueue->GetStreamId() == streamIndex){
                decoderQueue->PutPacket(packet);
                return 0;
            }
        }
        return -1;
    }

    bool QueueBox::IsStart()
    {
        return isStart;
    }
}