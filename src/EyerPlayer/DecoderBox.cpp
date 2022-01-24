#include "DecoderBox.hpp"

namespace Eyer
{
    DecoderBox::DecoderBox()
    {

    }

    DecoderBox::~DecoderBox()
    {

    }

    int DecoderBox::AddStream(const EyerAVStream & stream)
    {
        streamList.push_back(stream);
        return 0;
    }

    int DecoderBox::StartDeocder()
    {
        // 创建并且开启所有的解码器
        for(int i=0;i<streamList.size();i++){
            EyerDeocderQueueFFmpeg * decoder = new EyerDeocderQueueFFmpeg(streamList[i], &cvBox);
            decoder->StartDecode();
            decoderList.push_back(decoder);
        }
        return 0;
    }

    int DecoderBox::StopDecoder()
    {
        // 停止所有的解码器
        for(int i=0;i<decoderList.size();i++){
            decoderList[i]->StopDecode();
            delete decoderList[i];
        }
        decoderList.clear();
        streamList.clear();
        return 0;
    }

    int DecoderBox::PutPacket(EyerAVPacket * packet)
    {
        if(packet == nullptr){
            return -1;
        }
        for(int i=0;i<decoderList.size();i++){
            if(decoderList[i]->GetStreamId() == packet->GetStreamIndex()){
                decoderList[i]->PutPacket(packet);
                return 0;
            }
        }
        return -2;
    }

    int DecoderBox::GetPacketCacheSize()
    {
        int size = 0;
        for(int i=0;i<decoderList.size();i++){
            size += decoderList[i]->GetPacketCacheSize();
        }
        return size;
    }

    int DecoderBox::GetVideoStreamIndex()
    {
        int streamIndex = -1;
        for(int i=0;i<streamList.size();i++) {
            if(streamList[i].GetType() == EyerAVCodecType::MEDIA_TYPE_VIDEO) {
                streamIndex = streamList[i].GetStreamId();
            }
        }
        return streamIndex;
    }

    int DecoderBox::GetAudioStreamIndex()
    {
        int streamIndex = -1;
        for(int i=0;i<streamList.size();i++) {
            if(streamList[i].GetType() == EyerAVCodecType::MEDIA_TYPE_AUDIO) {
                streamIndex = streamList[i].GetStreamId();
            }
        }
        return streamIndex;
    }
}