#include "EyerAVAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
}

#include "EyerAVReaderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"

#include "EyerNet/EyerNet.hpp"
#include "EyerDASH/EyerDASH.hpp"


int read_packet(void *opaque, uint8_t *buf, int buf_size)
{
    Eyer::EyerDASHReader * dashReader = (Eyer::EyerDASHReader * )opaque;
    return dashReader->read_packet(opaque, buf, buf_size);
}

int64_t seek_func(void *opaque, int64_t offset, int whence)
{
    printf("Miaomiao seek_func offset: %lld, whence: %d\n", offset, whence);
    return -1;
}

namespace Eyer
{
    EyerAVReader::EyerAVReader(EyerString _path)
    {
        piml = new EyerAVReaderPrivate();
        piml->path = _path;

        av_register_all();
        avformat_network_init();


        int nBufferSize = 1024 * 1024 * 2;
        unsigned char * pBuffer = new unsigned char[nBufferSize];

        // EyerDASHReader * dashReader = new EyerDASHReader(EyerString("https://dash.akamaized.net/akamai/bbb_30fps/bbb_30fps.mpd"));
        EyerDASHReader * dashReader = new EyerDASHReader(EyerString("https://redknot.cn/DASH/xiaomai_dash.mpd"));

        AVIOContext* pIOCtx = avio_alloc_context(pBuffer, nBufferSize,
                                                 0,
                                                 dashReader,
                                                 read_packet,
                                                 0,
                                                 0);



        piml->formatCtx = avformat_alloc_context();

        piml->formatCtx->pb = pIOCtx;

    }

    EyerAVReader::~EyerAVReader()
    {
        if(piml->formatCtx != NULL){
            Close();
            avformat_free_context(piml->formatCtx);
            piml->formatCtx = NULL;
        }

        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVReader::GetVideoStreamIndex()
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        int videoStream = av_find_best_stream(piml->formatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

        return videoStream;
    }

    int EyerAVReader::GetAudioStreamIndex()
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        int audioStream = av_find_best_stream(piml->formatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

        return audioStream;
    }

    int EyerAVReader::Seek(double time)
    {
        /**
        * Seek to the keyframe at timestamp.
        * 'timestamp' in 'stream_index'.
        *
        * @param s media file handle
        * @param stream_index If stream_index is (-1), a default
        * stream is selected, and timestamp is automatically converted
        * from AV_TIME_BASE units to the stream specific time_base.
        * @param timestamp Timestamp in AVStream.time_base units
        *        or, if no stream is specified, in AV_TIME_BASE units.
        * @param flags flags which select direction and seeking mode
        * @return >= 0 on success
        */
        int64_t t = time * AV_TIME_BASE;
        int ret = av_seek_frame(piml->formatCtx, -1, t, AVSEEK_FLAG_BACKWARD);
        return ret;
    }

    int EyerAVReader::SeekFrame(int streamIndex, double timestamp)
    {
        int64_t t = timestamp / av_q2d(piml->formatCtx->streams[streamIndex]->time_base);
        return SeekFrame(streamIndex, t);
    }

    int EyerAVReader::SeekFrame(int streamIndex, int64_t timestamp)
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功
        /**
         * Seek to the keyframe at timestamp.
         * 'timestamp' in 'stream_index'.
         *
         * @param s media file handle
         * @param stream_index If stream_index is (-1), a default
         * stream is selected, and timestamp is automatically converted
         * from AV_TIME_BASE units to the stream specific time_base.
         * @param timestamp Timestamp in AVStream.time_base units
         *        or, if no stream is specified, in AV_TIME_BASE units.
         * @param flags flags which select direction and seeking mode
         * @return >= 0 on success
         */
        int ret = av_seek_frame(piml->formatCtx, streamIndex, timestamp, AVSEEK_FLAG_BACKWARD);

        return ret;
    }

    int EyerAVReader::Open()
    {
        int ret = avformat_open_input(&piml->formatCtx, piml->path.str, NULL, NULL);
        if(ret){
            return -1;
        }

        avformat_find_stream_info(piml->formatCtx, NULL);

        av_dump_format(piml->formatCtx, 0, piml->path.str, 0);

        return 0;
    }

    int EyerAVReader::Close()
    {
        avformat_close_input(&piml->formatCtx);
        return 0;
    }

    int EyerAVReader::Read(EyerAVPacket * packet)
    {
        int ret = av_read_frame(piml->formatCtx, packet->piml->packet);
        return ret;
    }

    int EyerAVReader::GetStreamCount()
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功

        return piml->formatCtx->nb_streams;
    }

    double EyerAVReader::GetDuration()
    {
        return piml->formatCtx->duration / 1000000;
    }

    int EyerAVReader::GetStream(EyerAVStream & stream, int index)
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功
        if(index < 0){
            return -1;
        }
        if(index >= GetStreamCount()) {
            return -1;
        }


        double duration = piml->formatCtx->streams[index]->duration * 1.0 * piml->formatCtx->streams[index]->time_base.num / piml->formatCtx->streams[index]->time_base.den;
        stream.SetDuration(duration);
        stream.streamIndex = piml->formatCtx->streams[index]->index;
        stream.piml->type = EyerAVStreamType::STREAM_TYPE_UNKNOW;

        avcodec_parameters_copy(stream.piml->codecpar, piml->formatCtx->streams[index]->codecpar);
        avcodec_copy_context(stream.piml->codec, piml->formatCtx->streams[index]->codec);

        EyerAVRational timebase;
        GetStreamTimeBase(timebase, index);
        stream.timebase = timebase;



        return 0;
    }

    int EyerAVReader::GetStreamTimeBase(EyerAVRational & rational, int streamIndex)
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


    int EyerAVReader::PrintInfo()
    {
        EyerLog("=============================\n");

        EyerLog("Url: %s\n", piml->path.str);

        int streamCount = GetStreamCount();
        EyerLog("Stream Count: %d\n", streamCount);

        for(int index=0;index<streamCount;index++){
            EyerLog("# Stream %d:\n", index);
            double duration = piml->formatCtx->streams[index]->duration * 1.0 * piml->formatCtx->streams[index]->time_base.num / piml->formatCtx->streams[index]->time_base.den;
            EyerLog("    Duration: %f s\n", duration);
        }

        EyerLog("=============================\n");
        return 0;
    }
}
