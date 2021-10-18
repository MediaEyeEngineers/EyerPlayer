#include "EyerAVReader.hpp"

#include "EyerAVReaderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"

namespace Eyer {
    EyerAVReader::EyerAVReader(EyerString _path) {
        piml = new EyerAVReaderPrivate();

        piml->path = _path;

        av_register_all();
        avformat_network_init();

        piml->formatCtx = avformat_alloc_context();
    }

    EyerAVReader::~EyerAVReader() {
        if (piml->formatCtx != NULL) {
            Close();
            avformat_free_context(piml->formatCtx);
            piml->formatCtx = NULL;
        }
        if (piml != nullptr) {
            delete piml;
            piml = nullptr;
        }
    }

    int EyerAVReader::Open() {
        int ret = avformat_open_input(&piml->formatCtx, piml->path.str, NULL, NULL);
        if (ret) {
            // TODO Error Code
            return ret;
        }

        avformat_find_stream_info(piml->formatCtx, NULL);
        // av_dump_format(piml->formatCtx, 0, piml->path.str, 0);

        // piml->formatCtx->streams[0]->codecpar->extradata

        return ret;
    }

    int EyerAVReader::Close() {
        avformat_close_input(&piml->formatCtx);
        return 0;
    }

    int EyerAVReader::GetStreamCount()
    {
        return piml->formatCtx->nb_streams;
    }

    int EyerAVReader::GetStream(EyerAVStream & stream, int index)
    {
        stream.piml->stream_id = piml->formatCtx->streams[index]->index;
        stream.piml->timebase = piml->formatCtx->streams[index]->time_base;
        return avcodec_parameters_copy(stream.piml->codecpar, piml->formatCtx->streams[index]->codecpar);
    }

    EyerAVStream EyerAVReader::GetStream(int index)
    {
        EyerAVStream stream;
        stream.piml->stream_id = piml->formatCtx->streams[index]->index;
        stream.piml->timebase = piml->formatCtx->streams[index]->time_base;
        avcodec_parameters_copy(stream.piml->codecpar, piml->formatCtx->streams[index]->codecpar);
        return stream;
    }

    int EyerAVReader::GetTimebase(EyerAVRational & timebase, int streamIndex)
    {
        timebase.num = piml->formatCtx->streams[streamIndex]->time_base.num;
        timebase.den = piml->formatCtx->streams[streamIndex]->time_base.den;
        return 0;
    }

    double EyerAVReader::GetDuration()
    {
        return piml->formatCtx->duration / AV_TIME_BASE;
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

    int EyerAVReader::Read(EyerAVPacket & packet)
    {
        int ret = av_read_frame(piml->formatCtx, packet.piml->packet);
        return ret;
    }

    int EyerAVReader::GetVideoStreamIndex() const
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        int videoStream = av_find_best_stream(piml->formatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

        return videoStream;
    }

    int EyerAVReader::GetAudioStreamIndex() const
    {
        if (piml->formatCtx == nullptr) {
            return -1;
        }

        int audioStream = av_find_best_stream(piml->formatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

        return audioStream;
    }
}