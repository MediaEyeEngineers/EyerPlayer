#ifndef	EYER_LIB_AV_H
#define	EYER_LIB_AV_H

#include "EyerCore/EyerCore.hpp"
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

namespace Eyer
{
    class EyerAVPacket;
    class EyerAVReader;
    class EyerAVDecoder;
    class EyerAVStream;
    class EyerAVEncoder;

    class EyerAVPacketPrivate;
    class EyerAVReaderPrivate;
    class EyerAVDecoderPrivate;
    class EyerAVStreamPrivate;
    class EyerAVFramePrivate;
    class EyerAVEncoderPrivate;
    class EyerAVWriterPrivate;

    class EyerAVAudioFrameUtil;
    class EyerAVFrameWeight;
    class EyerAVRational;

    enum EyerAVPixelFormat
    {
        Eyer_AV_PIX_FMT_UNKNOW = 0,
        Eyer_AV_PIX_FMT_YUV420P = 101,
        Eyer_AV_PIX_FMT_YUVJ420P = 102,
        Eyer_AV_PIX_FMT_YUV444P = 103,
        Eyer_AV_PIX_FMT_YUVJ444P = 104,
        Eyer_AV_PIX_FMT_YUVNV12 = 105,
        Eyer_AV_PIX_FMT_YUVNV21 = 106,
    };

    enum EyerAVStreamType{
        STREAM_TYPE_UNKNOW = 0,
        STREAM_TYPE_AUDIO = 1,
        STREAM_TYPE_VIDEO = 2
    };

    enum EyerAVFormat
    {
        EYER_AV_SAMPLE_FMT_FLTP = 1
    };

    class EyerAVPacket
    {
    public:
        EyerAVPacketPrivate * piml = nullptr;
    public:
        EyerAVPacket();
        ~EyerAVPacket();

        int GetStreamId();

        uint64_t GetPTS();
        uint64_t GetDTS();

        int RescaleTs(Eyer::EyerAVRational & codecTimebase, Eyer::EyerAVRational & streamTimebase);

        int SetPTS(uint64_t pts);
        int SetDTS(uint64_t dts);

        int SetStreamId(int id);
    };

    enum EyerAVAudioDateType
    {
        UNSIGNEDINT,
        SIGNEDINT,
        FLOAT
    };

    class EyerAVFrame
    {
    public:
        EyerAVFramePrivate * piml = nullptr;

        std::vector<void *> dataManager;

        int custom = 0;

        double timePts = 0.0;
    public:
        EyerAVFrame();
        ~EyerAVFrame();

        EyerAVFrame(const EyerAVFrame & frame);
        EyerAVFrame & operator = (const EyerAVFrame & frame);

        int SetPTS(int64_t pts);
        int64_t GetPTS();

        int GetYData(unsigned char * yData);
        int GetUData(unsigned char * uData);
        int GetVData(unsigned char * vData);
        int GetUVData(unsigned char * uvData);

        float GetAudioFloatData(int channel, int index);
        int SetAudioFloatData(int channel, int index, float d);

        int GetAudioPackedData(unsigned char * data);

        int GetAudioData(unsigned char * data);
        int SetAudioData(unsigned char * data, int dataLen, int nbSamples, int channel, EyerAVFormat format);

        int GetLineSize(int channel);

        int SetVideoData420P(unsigned char * y, unsigned char * u, unsigned char * v, int width, int height);

        int GetWidth();
        int GetHeight();

        int GetChannels();
        int GetNBSamples();
        int GetPerSampleSize();
        int GetSampleRate();
        EyerAVAudioDateType GetAudioDateType();

        int InitAACFrame(int channels);

        int GetInfo();

        EyerAVPixelFormat GetPixFormat() const;
    };

    class EyerAVReader
    {
    public:
        EyerAVReaderPrivate * piml = nullptr;
    public:
        EyerAVReader(EyerString _path);
        ~EyerAVReader();

        int Open();
        int Close();

        double GetDuration();

        int SeekFrame(int streamIndex, int64_t timestamp);
        int SeekFrame(int streamIndex, double timestamp);

        int Read(EyerAVPacket * packet);

        int GetStreamCount();
        int GetStream(EyerAVStream & stream, int index);

        int GetStreamTimeBase(EyerAVRational & rational, int streamIndex);
    };

    class EyerAVWriter
    {
    public:
        EyerAVWriterPrivate * piml = nullptr;
    public:
        EyerAVWriter(EyerString _path);
        ~EyerAVWriter();

        int Open();
        int Close();

        int AddStream(EyerAVEncoder * encoder);

        int GetStreamTimeBase(EyerAVRational & rational, int streamIndex);

        int GetStreamTimeBaseDen(int streamIndex);
        int GetStreamTimeBaseNum(int streamIndex);

        int WriteHand();
        int WritePacket(EyerAVPacket * packet);
    };

    class EyerAVStream
    {
    public:
        int streamIndex = -1;
        EyerAVStreamPrivate * piml = nullptr;

        double duration = 0;
    public:
        EyerAVStream();
        ~EyerAVStream();

        EyerAVStreamType GetStreamType();

        int SetDuration(double _duration);
        double GetDuration();

        int GetWidth();
        int GetHeight();
    };

    class EyerAVDecoder
    {
    public:
        EyerAVDecoderPrivate * piml = nullptr;
    public:
        EyerAVDecoder();
        ~EyerAVDecoder();

        int Init(EyerAVStream * stream);
        int InitHW(EyerAVStream * stream);

        int SendPacket(EyerAVPacket * packet);
        int RecvFrame(EyerAVFrame * frame);

        int GetFrameSize();
        int GetSampleRate();
    };

    enum CodecId
    {
        CODEC_ID_UNKNOW = 0,
        CODEC_ID_H264 = 1,
        CODEC_ID_AAC = 2
    };

    class EncoderParam
    {
    public:
        CodecId codecId = CodecId::CODEC_ID_UNKNOW;
        int width = 0;
        int height = 0;
        int fps = 25;
    };

    class EyerAVEncoder
    {
    public:
        EyerAVEncoderPrivate * piml = nullptr;
    public:
        EyerAVEncoder();
        ~EyerAVEncoder();

        int GetTimeBase(EyerAVRational & rational);

        int _Init(EyerAVStream * stream);
        int Init(EncoderParam * param);

        int Flush();

        int GetFPS();

        int GetBufferSize();
        int GetFrameSize();
        int GetChannelNum();

        int SendFrame(EyerAVFrame * frame);
        int RecvPacket(EyerAVPacket * packet);
    };



    enum EyerAVBitmapFormat
    {
        BITMAP_FORMAT_RGBA8888 = 1,
    };

    class EyerAVBitmap
    {
    private:
        int width = 0;
        int height = 0;
        EyerAVBitmapFormat format = EyerAVBitmapFormat::BITMAP_FORMAT_RGBA8888;
        unsigned char * pixelData = nullptr;
    public:
        EyerAVBitmap();
        ~EyerAVBitmap();

        int SetRGBA8888(int w, int h, unsigned char * _pixelData);

        int GetW();
        int GetH();

        int SetW(int w);
        int SetH(int h);

        EyerAVBitmapFormat GetFormat();
    };

    class EyerAVRational
    {
    public:
        int num = 0;
        int den = 0;

        EyerAVRational();
        EyerAVRational(const EyerAVRational & avRational);
        ~EyerAVRational();

        EyerAVRational & operator = (const EyerAVRational & avRational);
    };


    class EyerAVFrameWeight
    {
    public:
        EyerAVFrameWeight();
        EyerAVFrameWeight(EyerAVFrame & frame, float weight);
        ~EyerAVFrameWeight();

        EyerAVFrameWeight(EyerAVFrameWeight & frameWeight);

        EyerAVFrameWeight & operator = (EyerAVFrameWeight & frameWeight);

    public:
        EyerAVFrame * frame = nullptr;
        float weight = 1.0;
    };

    class EyerAVAudioFrameUtil
    {
    public:
        EyerAVAudioFrameUtil();
        ~EyerAVAudioFrameUtil();

        int AddAudioFrame(EyerAVFrame & frame, float weight);
        int MergeAudioFrame(EyerAVFrame & outFrame);

    private:
        EyerLinkedList<EyerAVFrameWeight *> frameList;
    };




    enum EyerAVCropType
    {
        FIT_CENTER = 0,
        FIT_XY = 1
    };

    class EyerAVCropUtil
    {
    public:
        EyerAVCropUtil();
        ~EyerAVCropUtil();

        int GetCrop(int viewW, int viewH, int imageW, int imageH, int & targetW, int & targetH,EyerAVCropType cropType = EyerAVCropType::FIT_CENTER);
    };
}

#endif
