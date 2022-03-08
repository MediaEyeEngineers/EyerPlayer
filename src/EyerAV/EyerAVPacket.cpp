#include "EyerAVPacket.hpp"

#include "EyerAVReaderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"

namespace Eyer
{
    EyerAVPacket::EyerAVPacket()
    {
        piml = new EyerAVPacketPrivate();

        piml->packet = av_packet_alloc();
        // av_init_packet(piml->packet);
    }

    EyerAVPacket::EyerAVPacket(const EyerAVPacket & packet) : EyerAVPacket()
    {
        *this = packet;
    }

    EyerAVPacket::~EyerAVPacket()
    {
        if (piml->packet != nullptr) {
            av_packet_free(&piml->packet);
            piml->packet = nullptr;
        }

        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    EyerAVPacket & EyerAVPacket::operator = (const EyerAVPacket & packet)
    {
        if (piml->packet != nullptr) {
            av_packet_free(&piml->packet);
            piml->packet = nullptr;
        }

        piml->packet = av_packet_clone(packet.piml->packet);

        return *this;
    }

    int64_t EyerAVPacket::GetPTS()
    {
        return piml->packet->pts;
    }

    int EyerAVPacket::GetStreamIndex()
    {
        return piml->packet->stream_index;
    }

    int EyerAVPacket::SetStreamIndex(int streamIndex)
    {
        piml->packet->stream_index = streamIndex;
        return 0;
    }

    int EyerAVPacket::RescaleTs(const EyerAVRational & _codecTimebase, const EyerAVRational & _streamTimebase)
    {
        AVRational codecTimebase;
        codecTimebase.num = _codecTimebase.num;
        codecTimebase.den = _codecTimebase.den;

        AVRational streamTimebase;
        streamTimebase.num = _streamTimebase.num;
        streamTimebase.den = _streamTimebase.den;

        av_packet_rescale_ts(piml->packet, codecTimebase, streamTimebase);

        return 0;
    }

    int EyerAVPacket::GetSize()
    {
        return piml->packet->size;
    }

    uint8_t * EyerAVPacket::GetDatePtr()
    {
        return piml->packet->data;
    }

    double EyerAVPacket::GetSecPTS()
    {
        return piml->secPTS;
    }

}