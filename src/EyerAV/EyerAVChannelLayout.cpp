#include "EyerAVChannelLayout.hpp"

#include "EyerAVFFmpegHeader.hpp"

namespace Eyer
{
    EyerAVChannelLayout EyerAVChannelLayout::UNKNOW                                 (-1, -1);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_MONO                 (0,     AV_CH_LAYOUT_MONO);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO               (1,     AV_CH_LAYOUT_STEREO);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_2POINT1              (2,     AV_CH_LAYOUT_2POINT1);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_2_1                  (3,     AV_CH_LAYOUT_2_1);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_SURROUND             (4,     AV_CH_LAYOUT_SURROUND);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_3POINT1              (5,     AV_CH_LAYOUT_3POINT1);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_4POINT0              (6,     AV_CH_LAYOUT_4POINT0);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_4POINT1              (7,     AV_CH_LAYOUT_4POINT1);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_2_2                  (8,     AV_CH_LAYOUT_2_2);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_QUAD                 (9,     AV_CH_LAYOUT_QUAD);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_5POINT0              (10,    AV_CH_LAYOUT_5POINT0);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_5POINT1              (11,    AV_CH_LAYOUT_5POINT1);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_5POINT0_BACK         (12,    AV_CH_LAYOUT_5POINT0_BACK);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_5POINT1_BACK         (13,    AV_CH_LAYOUT_5POINT1_BACK);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT0              (14,    AV_CH_LAYOUT_6POINT0);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT0_FRONT        (15,    AV_CH_LAYOUT_6POINT0_FRONT);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_HEXAGONAL            (16,    AV_CH_LAYOUT_HEXAGONAL);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT1              (17,    AV_CH_LAYOUT_6POINT1);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT1_BACK         (18,    AV_CH_LAYOUT_6POINT1_BACK);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_6POINT1_FRONT        (19,    AV_CH_LAYOUT_6POINT1_FRONT);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT0              (20,    AV_CH_LAYOUT_7POINT0);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT0_FRONT        (21,    AV_CH_LAYOUT_7POINT0_FRONT);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT1              (22,    AV_CH_LAYOUT_7POINT1);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT1_WIDE         (23,    AV_CH_LAYOUT_7POINT1_WIDE);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_7POINT1_WIDE_BACK    (24,    AV_CH_LAYOUT_7POINT1_WIDE_BACK);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_OCTAGONAL            (25,    AV_CH_LAYOUT_OCTAGONAL);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_HEXADECAGONAL        (26,    AV_CH_LAYOUT_HEXADECAGONAL);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_STEREO_DOWNMIX       (27,    AV_CH_LAYOUT_STEREO_DOWNMIX);
    EyerAVChannelLayout EyerAVChannelLayout::EYER_AV_CH_LAYOUT_22POINT2             (28,    AV_CH_LAYOUT_22POINT2);

    EyerAVChannelLayout::EyerAVChannelLayout()
       : EyerAVChannelLayout(0, AV_CH_LAYOUT_MONO)
    {

    }

    EyerAVChannelLayout::EyerAVChannelLayout(int _id, uint64_t _ffmpegId)
    {
        id = _id;
        ffmpegId = _ffmpegId;
    }

    bool EyerAVChannelLayout::operator == (const EyerAVChannelLayout & format)
    {
        return id == format.id;
    }

    bool EyerAVChannelLayout::operator != (const EyerAVChannelLayout & format)
    {
        return id != format.id;
    }

    EyerAVChannelLayout EyerAVChannelLayout::GetByFFmpegId(uint64_t ffmpegId)
    {
        if(ffmpegId == AV_CH_LAYOUT_MONO){
            return EYER_AV_CH_LAYOUT_MONO;
        }
        else if(ffmpegId == AV_CH_LAYOUT_STEREO){
            return EYER_AV_CH_LAYOUT_STEREO;
        }
        else if(ffmpegId == AV_CH_LAYOUT_2POINT1){
            return EYER_AV_CH_LAYOUT_2POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_2_1){
            return EYER_AV_CH_LAYOUT_2_1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_SURROUND){
            return EYER_AV_CH_LAYOUT_SURROUND;
        }
        else if(ffmpegId == AV_CH_LAYOUT_3POINT1){
            return EYER_AV_CH_LAYOUT_3POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_4POINT0){
            return EYER_AV_CH_LAYOUT_4POINT0;
        }
        else if(ffmpegId == AV_CH_LAYOUT_4POINT1){
            return EYER_AV_CH_LAYOUT_4POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_2_2){
            return EYER_AV_CH_LAYOUT_2_2;
        }
        else if(ffmpegId == AV_CH_LAYOUT_QUAD){
            return EYER_AV_CH_LAYOUT_QUAD;
        }
        else if(ffmpegId == AV_CH_LAYOUT_5POINT0){
            return EYER_AV_CH_LAYOUT_5POINT0;
        }
        else if(ffmpegId == AV_CH_LAYOUT_5POINT1){
            return EYER_AV_CH_LAYOUT_5POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_5POINT0_BACK){
            return EYER_AV_CH_LAYOUT_5POINT0_BACK;
        }
        else if(ffmpegId == AV_CH_LAYOUT_5POINT1_BACK){
            return EYER_AV_CH_LAYOUT_5POINT1_BACK;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT0){
            return EYER_AV_CH_LAYOUT_6POINT0;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT0_FRONT){
            return EYER_AV_CH_LAYOUT_6POINT0_FRONT;
        }
        else if(ffmpegId == AV_CH_LAYOUT_HEXAGONAL){
            return EYER_AV_CH_LAYOUT_HEXAGONAL;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT1){
            return EYER_AV_CH_LAYOUT_6POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT1_BACK){
            return EYER_AV_CH_LAYOUT_6POINT1_BACK;
        }
        else if(ffmpegId == AV_CH_LAYOUT_6POINT1_FRONT){
            return EYER_AV_CH_LAYOUT_6POINT1_FRONT;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT0){
            return EYER_AV_CH_LAYOUT_7POINT0;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT0_FRONT){
            return EYER_AV_CH_LAYOUT_7POINT0_FRONT;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT1){
            return EYER_AV_CH_LAYOUT_7POINT1;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT1_WIDE){
            return EYER_AV_CH_LAYOUT_7POINT1_WIDE;
        }
        else if(ffmpegId == AV_CH_LAYOUT_7POINT1_WIDE_BACK){
            return EYER_AV_CH_LAYOUT_7POINT1_WIDE_BACK;
        }
        else if(ffmpegId == AV_CH_LAYOUT_OCTAGONAL){
            return EYER_AV_CH_LAYOUT_OCTAGONAL;
        }
        else if(ffmpegId == AV_CH_LAYOUT_HEXADECAGONAL){
            return EYER_AV_CH_LAYOUT_HEXADECAGONAL;
        }
        else if(ffmpegId == AV_CH_LAYOUT_STEREO_DOWNMIX){
            return EYER_AV_CH_LAYOUT_STEREO_DOWNMIX;
        }
        else if(ffmpegId == AV_CH_LAYOUT_22POINT2){
            return EYER_AV_CH_LAYOUT_22POINT2;
        }

        return UNKNOW;
    }

    int EyerAVChannelLayout::GetChannelLayoutNBChannels(EyerAVChannelLayout channelLayout)
    {
        return av_get_channel_layout_nb_channels(channelLayout.ffmpegId);
    }
}