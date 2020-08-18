#ifndef	EYER_LIB_AV_UTIL_H
#define	EYER_LIB_AV_UTIL_H

#include "EyerCore/EyerCore.hpp"
#include "../EyerAVAV.hpp"

namespace Eyer
{
    class EyerWandResource;
    class EyerWandVideoResource;
    class EyerVideoDecoderLine;

    class EyerWandResource {
    public:
        EyerString resPath;
    public:
        EyerWandResource();
        ~EyerWandResource();

        int SetPath(EyerString resPath);
    };

    class EyerWandVideoResource : public EyerWandResource {
    public:
        EyerWandVideoResource();
        ~EyerWandVideoResource();

        int GetVideoDuration(double & duration);
        int GetVideoFrame(EyerAVFrame & avFrame, double ts);

        int GetW();
        int GetH();
    private:
        EyerLinkedList<EyerVideoDecoderLine *> decoderLineList;

        int w = -1;
        int h = -1;

        std::mutex mut;
    };

    class EyerVideoDecoderLine
    {
    public:
        EyerVideoDecoderLine(EyerString resPath, double startTime, EyerAVStreamType type = EyerAVStreamType::STREAM_TYPE_VIDEO);
        ~EyerVideoDecoderLine();

        int Init();

        int GetFrame(EyerAVFrame & frame, double ts);

        double GetStartTime();
        int GetCacheFrameCount();
    private:
        EyerString resPath;
        EyerAVStreamType type = EyerAVStreamType::STREAM_TYPE_VIDEO;

        EyerAVReader * reader = nullptr;
        EyerAVDecoder * decoder = nullptr;
        int streamIndex = -1;
        double startTime = 0.0;
        int isEnd = 0;

        EyerLinkedList<EyerAVFrame *> frameList;

        int ReadFrame();
        int SelectFrameInList(EyerAVFrame & frame, double ts);

        int RemoveFrame();
    };
}

#endif