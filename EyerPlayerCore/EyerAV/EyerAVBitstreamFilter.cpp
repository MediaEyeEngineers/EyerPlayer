#include "EyerAVBitstreamFilter.hpp"

#include "EyerAVBitstreamFilterPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"

namespace Eyer {
    int EyerAVBitstreamFilter::QueryAllBitstreamFilter()
    {
        void *state = NULL;

        const AVBitStreamFilter * bsf = nullptr;
        while (bsf = av_bsf_next(&state)) {
            EyerLog("%s\n", bsf->name);
        }

        return 0;
    }

    EyerAVBitstreamFilter::EyerAVBitstreamFilter(EyerAVBitstreamFilterType type, EyerAVStream & stream)
    {
        piml = new EyerAVBitstreamFilterPrivate();

        const AVBitStreamFilter *bsf = av_bsf_get_by_name("h264_mp4toannexb");
        int ret = av_bsf_alloc(bsf, &piml->ctx);

        avcodec_parameters_copy(piml->ctx->par_in, stream.piml->codecpar);
        av_bsf_init(piml->ctx);
    }

    EyerAVBitstreamFilter::~EyerAVBitstreamFilter()
    {
        if(piml->ctx != nullptr){
            av_bsf_free(&piml->ctx);
            piml->ctx = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVBitstreamFilter::SendPacket(EyerAVPacket * packet)
    {
        int ret = 0;
        if(packet == nullptr){
            ret = av_bsf_send_packet(piml->ctx, nullptr);
        }
        else{
            ret = av_bsf_send_packet(piml->ctx, packet->piml->packet);
        }

        return ret;
    }

    int EyerAVBitstreamFilter::ReceivePacket(EyerAVPacket * packet)
    {
        int ret = 0;
        ret = av_bsf_receive_packet(piml->ctx, packet->piml->packet);
        return ret;
    }
}