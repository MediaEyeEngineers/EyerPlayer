#ifndef EYERLIB_EYERAVFRAME_HPP
#define EYERLIB_EYERAVFRAME_HPP

#include <stdint.h>
#include "EyerAVSampleFormat.hpp"
#include "EyerAVPixelFormat.hpp"
#include "EyerAVChannelLayout.hpp"

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

        int SetWidth(int width);
        int SetHeight(int height);
        int GetWidth();
        int GetHeight();

        int SetVideoData420P(unsigned char * _y, unsigned char * _u, unsigned char * _v, int _width, int _height);

        int SetAudioDataFLTP    (uint8_t * data, int & offset);

        int SetAudioDataS16_44100_2_1024 (uint8_t * data);

        int InitVideoData(EyerAVPixelFormat pixelFormat, int width, int height);
        int InitAudioData(EyerAVChannelLayout channelLayout, EyerAVSampleFormat sampleFormat, int sample_rate, int nb_samples);

        int Resample(EyerAVFrame & frame, EyerAVChannelLayout channelLayout, EyerAVSampleFormat sampleFormat, int sample_rate);

        int Scale(EyerAVFrame & frame, const EyerAVPixelFormat format, const int dstW, const int dstH);
        int Scale(EyerAVFrame & frame, const EyerAVPixelFormat format);
        int Scale(EyerAVFrame & frame, const int dstW, const int dstH);

        int Mirror(EyerAVFrame & frame, int type);

        uint8_t * GetData(int index = 0);
        int GetLinesize(int index = 0);

        EyerAVPixelFormat GetPixelFormat();

        int GetSampleRate();
        EyerAVChannelLayout GetChannelLayout();
        EyerAVSampleFormat GetSampleFormat();
        int GetSampleNB();

    public:
        EyerAVFramePrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVFRAME_HPP
