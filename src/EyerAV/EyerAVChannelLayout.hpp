#ifndef EYERLIB_EYERAVCHANNELLAYOUT_HPP
#define EYERLIB_EYERAVCHANNELLAYOUT_HPP

#include <stdint.h>

namespace Eyer
{
    class EyerAVChannelLayout
    {
    public:
        static EyerAVChannelLayout UNKNOW;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_MONO;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_STEREO;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_2POINT1;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_2_1;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_SURROUND;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_3POINT1;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_4POINT0;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_4POINT1;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_2_2;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_QUAD;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_5POINT0;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_5POINT1;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_5POINT0_BACK;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_5POINT1_BACK;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_6POINT0;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_6POINT0_FRONT;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_HEXAGONAL;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_6POINT1;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_6POINT1_BACK;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_6POINT1_FRONT;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_7POINT0;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_7POINT0_FRONT;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_7POINT1;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_7POINT1_WIDE;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_7POINT1_WIDE_BACK;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_OCTAGONAL;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_HEXADECAGONAL;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_STEREO_DOWNMIX;
        static EyerAVChannelLayout EYER_AV_CH_LAYOUT_22POINT2;

        EyerAVChannelLayout();
        EyerAVChannelLayout(int id, uint64_t ffmpegId);

        static EyerAVChannelLayout GetByFFmpegId(uint64_t ffmpegId);
        static int GetChannelLayoutNBChannels(EyerAVChannelLayout channelLayout);

        bool operator == (const EyerAVChannelLayout & format);
        bool operator != (const EyerAVChannelLayout & format);

        int id = 0;
        uint64_t ffmpegId = 0;
    };
}

#endif //EYERLIB_EYERAVCHANNELLAYOUT_HPP
