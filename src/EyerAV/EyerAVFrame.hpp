#ifndef EYERLIB_EYERAVFRAME_HPP
#define EYERLIB_EYERAVFRAME_HPP

#include <stdint.h>
#include "EyerAVSampleFormat.hpp"
#include "EyerAVPixelFormat.hpp"

namespace Eyer
{
    class EyerAVFramePrivate;

    class EyerAVFrame
    {
    public:
        EyerAVFrame();
        EyerAVFrame(const EyerAVFrame & frame);
        ~EyerAVFrame();

        EyerAVFrame & operator = (const EyerAVFrame & frame);

        int SetPTS(int64_t pts);
        int64_t GetPTS();
        double GetSecPTS();

        int GetWidth();
        int GetHeight();

        int SetVideoData420P(unsigned char * _y, unsigned char * _u, unsigned char * _v, int _width, int _height);

        int SetAudioDataFLTP    (uint8_t * data);

        int SetAudioDataS16_44100_2_1024 (uint8_t * data);


        int InitAudioData(EyerAVSampleFormat sampleFormat, int sample_rate, int nb_samples, int channels);

        int Resample(EyerAVFrame & frame, EyerAVSampleFormat sampleFormat, int sample_rate);

        int Scale(EyerAVFrame & frame, const EyerAVPixelFormat format, const int dstW, const int dstH);
        int Scale(EyerAVFrame & frame, const EyerAVPixelFormat format);

        uint8_t * GetData(int index = 0);
        int GetLinesize(int index = 0);

    public:
        EyerAVFramePrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVFRAME_HPP
