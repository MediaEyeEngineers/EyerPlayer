#include "AVUtil.hpp"
#include <math.h>

namespace Eyer
{
    EyerVideoDecoderLine::EyerVideoDecoderLine(EyerString _resPath, double _startTime, EyerAVStreamType _type)
    {
        resPath = _resPath;
        type = _type;
        startTime = _startTime;

        reader = new EyerAVReader(resPath);
    }

    EyerVideoDecoderLine::~EyerVideoDecoderLine()
    {
        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }

        if(reader != nullptr){
            reader->Close();

            delete reader;
            reader = nullptr;
        }
    }

    int EyerVideoDecoderLine::Init()
    {
        int ret = reader->Open();
        if(ret){
            return -1;
        }

        streamIndex = reader->GetVideoStreamIndex();
        if(streamIndex < 0){
            reader->Close();
            return -2;
        }

        reader->SeekFrame(streamIndex, startTime);

        EyerAVStream stream;
        ret = reader->GetStream(stream, streamIndex);
        if(ret){
            reader->Close();
            return -3;
        }

        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }

        decoder = new EyerAVDecoder();
        decoder->Init(&stream);
        
        return 0;
    }

    int EyerVideoDecoderLine::GetFrame(EyerAVFrame & frame, double ts)
    {
        int ret;
        while(1){
            // 先查看缓存列表中有没有合适的
            ret = SelectFrameInList(frame, ts);
            // EyerLog("SelectFrameInList Ret: %d\n", ret);
            if(!ret){
                return 0;
            }

            // 读取一帧进缓存
            ret = ReadFrame();
            RemoveFrame();
            // EyerLog("ReadFrame Ret: %d\n", ret);

            // 判断是否到了文件末尾
            if(isEnd){
                // 到了文件末尾，直接拿缓存最后一帧，拿到赶紧滚
                if(frameList.getLength() <= 0){
                    return -1;
                }

                EyerAVFrame * f = nullptr;
                frameList.find(frameList.getLength() - 1, f);

                if(f == nullptr){
                    return -1;
                }

                frame = *f;
                return 0;
            }
        }

        return 0;
    }

    double EyerVideoDecoderLine::GetStartTime()
    {
        if(reader == nullptr){
            return startTime;
        }

        if(frameList.getLength() <= 0){
            return startTime;
        }

        EyerAVFrame * frame = nullptr;
        frameList.find(0, frame);
        if(frame == nullptr){
            return startTime;
        }

        Eyer::EyerAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, streamIndex);

        double t = frame->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

        return t;
    }

    int EyerVideoDecoderLine::GetCacheFrameCount()
    {
        return frameList.getLength();
    }

    int EyerVideoDecoderLine::ReadFrame()
    {
        if(decoder == nullptr){
            return -1;
        }

        EyerAVPacket packet;
        int ret = reader->Read(&packet);
        if(ret){
            // 清空解码器
            ret = decoder->SendPacket(nullptr);
            if(ret){
                return -3;
            }
            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder->RecvFrame(frame);
                if(ret){
                    delete frame;
                    break;
                }

                frameList.insertBack(frame);
            }
            isEnd = 1;
        }
        else{
            if(packet.GetStreamId() != streamIndex){
                return -2;
            }
            ret = decoder->SendPacket(&packet);
            if(ret){
                return -3;
            }
            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder->RecvFrame(frame);
                if(ret){
                    delete frame;
                    break;
                }

                frameList.insertBack(frame);
            }
        }

        return 0;
    }

    int EyerVideoDecoderLine::SelectFrameInList(EyerAVFrame & frame, double ts)
    {
        Eyer::EyerAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, streamIndex);

        if(frameList.getLength() <= 0){
            return -1;
        }
        /*
        if(frameList.getLength() == 1)
            EyerAVFrame * f = nullptr;
            frameList.find(0, f);
            if(f == nullptr){
                return -2;
            }

            double t = f->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;
        }
        */

        EyerAVFrame * frameP = nullptr;

        for(int i=1;i<frameList.getLength();i++){ 
            EyerAVFrame * fb = nullptr;
            frameList.find(i, fb);
            if(fb == nullptr){
                continue;
            }

            double tb = fb->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

            EyerAVFrame * fa = nullptr;
            frameList.find(i - 1, fa);
            if(fa == nullptr){
                continue;
            }

            double ta = fa->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

            if(ts == ta){
                frameP = fa;
            }
            if(ts == tb){
                frameP = fb;
            }

            if(ts > ta && ts < tb){
                // 落到中间了
                if(abs(ts - ta) > abs(ts - tb)){
                    frameP = fb;
                }
                else{
                    frameP = fa;
                }
            }

            if(ts < ta && ts < tb){
                //出错了
                return -3;
            }

            if(ts > ta && ts > tb){

            }
        }

        if(frameP != nullptr){
            frame = *frameP;
        }

        if(frameP == nullptr){
            return -4;
        }

        return 0;
    }

    int EyerVideoDecoderLine::RemoveFrame()
    {
        while(frameList.getLength() > 15){
            EyerAVFrame * f = nullptr;
            frameList.find(0, f);
            if(f != nullptr){
                delete f;
            }
            frameList.deleteEle(0);
        }
        return 0;
    }
}