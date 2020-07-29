#include "AVUtil.hpp"

namespace Eyer
{
    EyerWandVideoResource::EyerWandVideoResource()
    {

    }

    EyerWandVideoResource::~EyerWandVideoResource()
    {
        std::lock_guard<std::mutex> lock(mut);

        for(int i=0;i<decoderLineList.getLength();i++){
            EyerVideoDecoderLine * decoderLine = nullptr;
            decoderLineList.find(i, decoderLine);
            if(decoderLine != nullptr){
                delete decoderLine;
            }
        }
        decoderLineList.clear();
    }

    int EyerWandVideoResource::GetVideoFrame(EyerAVFrame & avFrame, double ts)
    {
        std::lock_guard<std::mutex> lock(mut);

        // 将多余的 Decoder Line 删除
        while(decoderLineList.getLength() > 5){
            EyerVideoDecoderLine * dl = nullptr;
            decoderLineList.find(0, dl);
            if(dl != nullptr){
                delete dl;
            }
            decoderLineList.deleteEle(0);
        }

        // 统计一下当前一共缓冲了多少帧 Debug 用
        int cacheFrameCount = 0;
        for(int i=0;i<decoderLineList.getLength();i++) {
            EyerVideoDecoderLine * dl = nullptr;
            decoderLineList.find(i, dl);
            if(dl != nullptr){
                cacheFrameCount += dl->GetCacheFrameCount();
            }
        }

        // EyerLog("Cache Frame Count: %d\n", cacheFrameCount);

        // 搜索合适的 Decoder Line
        EyerVideoDecoderLine * decoderLine = nullptr;
        for(int i=0;i<decoderLineList.getLength();i++) {
            EyerVideoDecoderLine * dl = nullptr;
            decoderLineList.find(i, dl);
            if(ts >= dl->GetStartTime()){
                decoderLine = dl;
            }
        }

        // 搜索不到的情况下新建一个 Decoder Line
        if(decoderLine == nullptr){
            decoderLine = new EyerVideoDecoderLine(resPath, ts);
            int ret = decoderLine->Init();
            if(ret){
                delete decoderLine;
                decoderLine = nullptr;
            }
            else{
                decoderLineList.insertBack(decoderLine);
            }
        }

        if(decoderLine == nullptr){
            return -1;
        }

        decoderLine->GetFrame(avFrame, ts);

        return 0;
    }

    int EyerWandVideoResource::GetVideoDuration(double & duration)
    {
        std::lock_guard<std::mutex> lock(mut);

        int finalRet = 0;

        Eyer::EyerAVReader reader(resPath);
        int videoStreamIndex = -1;
        EyerAVStream avStream;

        int ret = reader.Open();
        if(ret){
            finalRet = -1;
            goto END;
        }

        videoStreamIndex = reader.GetVideoStreamIndex();

        if(videoStreamIndex < 0){
            finalRet = -1;
            goto END;
        }

        ret = reader.GetStream(avStream, videoStreamIndex);
        if(ret){
            finalRet = -1;
            goto END;
        }

        finalRet = 0;
        duration = avStream.GetDuration();

        w = avStream.GetWidth();
        h = avStream.GetHeight();

    END:
        ret = reader.Close();

        return finalRet;
    }


    int EyerWandVideoResource::GetW()
    {
        if(w <= 0) {
            double duration;
            GetVideoDuration(duration);
        }
        return w;
    }

    int EyerWandVideoResource::GetH()
    {
        if(h <= 0) {
            double duration;
            GetVideoDuration(duration);
        }
        return h;
    }
}