#include "EyerAVBitstreamFilter.hpp"

#include "EyerAVBitstreamFilterPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"

namespace Eyer {
    EyerAVBitstreamFilter::EyerAVBitstreamFilter()
    {
        piml = new EyerAVBitstreamFilterPrivate();
        piml->h264bsfc = av_bitstream_filter_init("h264_mp4toannexb");
    }

    EyerAVBitstreamFilter::~EyerAVBitstreamFilter()
    {
        if(piml->h264bsfc != nullptr){
            av_bitstream_filter_close(piml->h264bsfc);
            piml->h264bsfc = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    /*
    int EyerAVBitstreamFilter::Filter(EyerAVStream & stream, unsigned char * * dstData, int * dstLen, unsigned char * srcData, int srcLen)
    {
        int ret = 0;
        // int ret = av_bitstream_filter_filter(piml->h264bsfc, ifmt_ctx->streams[videoindex]->codec, NULL, &pkt.data, &pkt.size, pkt.data, pkt.size, 0);
        return ret;
    }
     */

    int EyerAVBitstreamFilter::Filter(EyerAVStream & stream, EyerAVPacket * pkt, unsigned char * * dstData, int * dstLen)
    {
        int ret = av_bitstream_filter_filter(
                piml->h264bsfc,
                stream.piml->codec,
                NULL,
                dstData,
                dstLen,
                pkt->piml->packet->data,
                pkt->piml->packet->size, 0);
        return ret;
    }
}