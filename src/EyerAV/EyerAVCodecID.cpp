#include "EyerAVCodecID.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVCodecID EyerAVCodecID::CODEC_ID_H264  (101, AV_CODEC_ID_H264);
    EyerAVCodecID EyerAVCodecID::CODEC_ID_H265  (102, AV_CODEC_ID_H265);

    EyerAVCodecID EyerAVCodecID::CODEC_ID_AAC   (201, AV_CODEC_ID_AAC);
    EyerAVCodecID EyerAVCodecID::CODEC_ID_MP3   (202, AV_CODEC_ID_MP3);

    EyerAVCodecID::EyerAVCodecID()
    {

    }

    EyerAVCodecID::EyerAVCodecID(int _id, int _ffmpegId)
    {
        id = _id;
        ffmpegId = _ffmpegId;
    }

    bool EyerAVCodecID::operator == (const EyerAVCodecID & format)
    {
        return id = format.id;
    }
}