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
            ThreadDecode * decodeThread = new ThreadDecode(stream, this);
            decodeThread->Start();
            decoderList.push_back(decodeThread);
        }
        return 0;
    }

    int QueueBox::StopDecoder()
    {
        for(int i=0; i<decoderList.size(); i++) {
            ThreadDecode * decodeThread = decoderList[i];
            decodeThread->Stop();
            delete decodeThread;
        }
        decoderList.clear();
        return 0;
    }

    int QueueBox::GetPacketQueueCacheSize()
    {
        int size = 0;
        for(int i=0; i<decoderList.size(); i++) {
            ThreadDecode *decodeThread = decoderList[i];
            size += decodeThread->packetCacheSize;
        }
        return size;
    }

    int QueueBox::PutPacket(EyerAVPacket * packet)
    {
        int streamIndex = packet->GetStreamIndex();
        for(int i=0; i<decoderList.size(); i++){
            ThreadDecode * decodeThread = decoderList[i];
            if(decodeThread->GetStreamId() == streamIndex){
                decodeThread->PutPacket(packet);
                return 0;
            }
        }
        return -1;
    }
}