#include "EyerAVChannelLayout.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVChannelLayout EyerAVChannelLayout::CH_LAYOUT_STEREO(1, AV_CH_LAYOUT_STEREO);

    EyerAVChannelLayout::EyerAVChannelLayout()
       : EyerAVChannelLayout(1, AV_CH_LAYOUT_STEREO)
    {

    }

    EyerAVChannelLayout::EyerAVChannelLayout(int _id, int _ffmpegId)
    {
        id = _id;
        ffmpegId = _ffmpegId;
    }

    bool EyerAVChannelLayout::operator == (const EyerAVChannelLayout & format)
    {
        return id == format.id;
    }
}