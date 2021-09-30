#include "EyerAVSampleFormat.hpp"

namespace Eyer
{
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_U8    (0);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S16   (1);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S32   (2);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_FLT   (3);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_DBL   (4);

    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_U8P   (5);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S16P  (6);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_S32P  (7);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_FLTP  (8);
    EyerAVSampleFormat EyerAVSampleFormat::SAMPLE_FMT_DBLP  (9);

    EyerAVSampleFormat::EyerAVSampleFormat(int _id)
    {
        id = _id;
    }

    bool EyerAVSampleFormat::operator == (const EyerAVSampleFormat & format)
    {
        return id == format.id;
    }
}