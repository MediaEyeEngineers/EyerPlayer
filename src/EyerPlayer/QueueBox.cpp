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
            EyerDeocdeQueue * decoderQueue = new EyerDeocdeQueueFFmpeg(stream);
            decoderQueue->Start();
            decoderQueueList.push_back(decoderQueue);
        }
        return 0;
    }

    int QueueBox::StopDecoder()
    {
        for(int i=0; i<decoderQueueList.size(); i++) {
            EyerDeocdeQueue * decoderQueue = decoderQueueList[i];
            decoderQueue->Stop();
            delete decoderQueue;
        }
        decoderQueueList.clear();
        return 0;
    }

    int QueueBox::GetPacketQueueCacheSize()
    {
        /*
        int size = 0;
        for(int i=0; i<decoderList.size(); i++) {
            ThreadDecode *decodeThread = decoderList[i];
            size += decodeThread->packetCacheSize;
        }
        return size;
         */

        return 0;
    }

    int QueueBox::PutPacket(EyerAVPacket * packet)
    {
        /*
        int streamIndex = packet->GetStreamIndex();
        for(int i=0; i<decoderList.size(); i++){
            ThreadDecode * decodeThread = decoderList[i];
            if(decodeThread->GetStreamId() == streamIndex){
                decodeThread->PutPacket(packet);
                return 0;
            }
        }
        */
        return -1;
    }
}