#ifndef EYERLIB_EYERAVCHANNELLAYOUT_HPP
#define EYERLIB_EYERAVCHANNELLAYOUT_HPP

namespace Eyer
{
    class EyerAVChannelLayout
    {
    public:
        static EyerAVChannelLayout CH_LAYOUT_STEREO;

        EyerAVChannelLayout();
        EyerAVChannelLayout(int id, int ffmpegId);

        bool operator == (const EyerAVChannelLayout & format);

        int id = 0;
        int ffmpegId = 0;
    };
}

#endif //EYERLIB_EYERAVCHANNELLAYOUT_HPP
