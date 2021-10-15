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
            ThreadDecode * decoderThread = new ThreadDecode(stream, this);
            decoderList.push_back(decoderThread);
            decoderThread->Start();
        }
        return 0;
    }

    int QueueBox::StopDecoder()
    {
        for(int i=0;i<decoderList.size();i++){
            ThreadDecode * decoderThread = decoderList[i];
            decoderThread->Stop();
            delete decoderThread;
        }
        decoderList.clear();
        return 0;
    }

    int QueueBox::GetPacketQueueCacheSize()
    {
        return packetCacheSize;
    }

    int QueueBox::PutPacket(EyerAVPacket * packet)
    {
        for(int i=0;i<decoderList.size();i++) {
            ThreadDecode * decoderThread = decoderList[i];
            if(decoderThread->GetStreamId() == packet->GetStreamIndex()){
                packetCacheSize += packet->GetSize();
                break;
            }
        }
        return 0;
    }
}