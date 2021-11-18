#include "EyerAVSampleFormat.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_U8    (0, AV_SAMPLE_FMT_U8);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S16   (1, AV_SAMPLE_FMT_S16);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S32   (2, AV_SAMPLE_FMT_S32);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_FLT   (3, AV_SAMPLE_FMT_FLT);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_DBL   (4, AV_SAMPLE_FMT_DBL);

    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_U8P   (5, AV_SAMPLE_FMT_U8P);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S16P  (6, AV_SAMPLE_FMT_S16P);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S32P  (7, AV_SAMPLE_FMT_S32P);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_FLTP  (8, AV_SAMPLE_FMT_FLTP);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_DBLP  (9, AV_SAMPLE_FMT_DBLP);

    EyerAVSampleFormat::EyerAVSampleFormat()
    {

    }

    EyerAVSampleFormat::EyerAVSampleFormat(int _id, int _ffmpegId)
    {
        id = _id;
        ffmpegId = _ffmpegId;
    }

    EyerAVSampleFormat::EyerAVSampleFormat(const EyerAVSampleFormat & sampleFormat)
    {
        *this = sampleFormat;
    }

    EyerAVSampleFormat & EyerAVSampleFormat::operator = (const EyerAVSampleFormat & sampleFormat)
    {
        id = sampleFormat.id;
        ffmpegId = sampleFormat.ffmpegId;
        return *this;
    }

    bool EyerAVSampleFormat::operator == (const EyerAVSampleFormat & format)
    {
        return id == format.id;
    }
}