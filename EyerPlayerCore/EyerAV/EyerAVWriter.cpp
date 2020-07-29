#include "EyerAVAV.hpp"

#include "EyerAVStreamPrivate.hpp"
#include "EyerAVDecoderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVFramePrivate.hpp"
#include "EyerAVEncoderPrivate.hpp"
#include "EyerAVWriterPrivate.hpp"

namespace Eyer
{
    EyerAVWriter::EyerAVWriter(EyerString _path)
    {
        piml = new EyerAVWriterPrivate();
        piml->path = _path;
        // av_register_all();
        avformat_network_init();

        avformat_alloc_output_context2(&piml->formatCtx, NULL, NULL, piml->path.str);
    }

    EyerAVWriter::~EyerAVWriter()
    {
        if(piml->formatCtx != NULL){
            avformat_free_context(piml->formatCtx);
            piml->formatCtx = NULL;
        }

        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVWriter::Open()
    {
        int ret = avio_open(&piml->formatCtx->pb, piml->path.str, AVIO_FLAG_WRITE);
        if(ret){
            return -1;
        }

        return 0;
    }

    int EyerAVWriter::Close()
    {
        av_write_trailer(piml->formatCtx);
        avio_close(piml->formatCtx->pb);
        return 0;
    }

    int EyerAVWriter::AddStream(EyerAVEncoder * encoder)
    {
        if(encoder->piml->codecContext == nullptr){
            return -1;
        }
        
        AVStream * avStream = avformat_new_stream(piml->formatCtx, encoder->piml->codecContext->codec);

        avcodec_parameters_from_context(avStream->codecpar, encoder->piml->codecContext);

        avStream->time_base = encoder->piml->codecContext->time_base;
        avStream->codecpar->codec_tag = 0;

        encoder->piml->codecContext->codec_tag = 0;
        
        return avStream->index;
    }

    int EyerAVWriter::GetStreamTimeBase(EyerAVRational & rational, int streamIndex)
    {
        if(streamIndex < 0){
            return -1;
        }
        if(streamIndex >= piml->formatCtx->nb_streams){
            return -1;
        }

        rational.num = piml->formatCtx->streams[streamIndex]->time_base.num;
        rational.den = piml->formatCtx->streams[streamIndex]->time_base.den;

        return 0;
    }

    int EyerAVWriter::GetStreamTimeBaseDen(int streamIndex)
    {
        if(streamIndex < 0){
            return -1;
        }
        if(streamIndex >= piml->formatCtx->nb_streams){
            return -1;
        }

        return piml->formatCtx->streams[streamIndex]->time_base.den;
    }

    int EyerAVWriter::GetStreamTimeBaseNum(int streamIndex)
    {
        if(streamIndex < 0){
            return -1;
        }
        if(streamIndex >= piml->formatCtx->nb_streams){
            return -1;
        }

        return piml->formatCtx->streams[streamIndex]->time_base.num;
    }

    int EyerAVWriter::WritePacket(EyerAVPacket * packet)
    {
        int ret = av_interleaved_write_frame(piml->formatCtx, packet->piml->packet);
        return ret;
    }

    int EyerAVWriter::WriteHand()
    {
        int ret = avformat_write_header(piml->formatCtx, nullptr);
        return 0;
    }
}
