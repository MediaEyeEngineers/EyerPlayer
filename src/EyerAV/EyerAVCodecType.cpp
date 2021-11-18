#include "EyerAVCodecType.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVCodecType EyerAVCodecType::MEDIA_TYPE_VIDEO(1, AVMEDIA_TYPE_VIDEO);
    EyerAVCodecType EyerAVCodecType::MEDIA_TYPE_AUDIO(2, AVMEDIA_TYPE_AUDIO);

    EyerAVCodecType::EyerAVCodecType()
    {

    }

    EyerAVCodecType::EyerAVCodecType(int _id, int _ffmpegId)
    {
        id = _id;
        ffmpegId = _ffmpegId;
    }

    bool EyerAVCodecType::operator == (const EyerAVCodecType & codecType)
    {
        return id == codecType.id;
    }
}