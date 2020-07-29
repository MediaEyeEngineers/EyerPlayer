#include "EyerAVAV.hpp"

namespace Eyer
{
    EyerAVTool::EyerAVTool(){

    }

    EyerAVTool::~EyerAVTool(){

    }

    int EyerAVTool::GetYUVLen(const EyerAVFrame & avframe, EyerYUVLen & yuvLen)
    {
        return GetYUVLen(avframe.GetWidth(), avframe.GetHeight(), yuvLen, avframe.GetPixFormat());
    }
    
    int EyerAVTool::GetYUVLen(int w, int h, EyerYUVLen & yuvLen, EyerAVPixelFormat format)
    {
        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_UNKNOW){
            yuvLen.yLen = 0;
            yuvLen.uLen = 0;
            yuvLen.vLen = 0;
            yuvLen.uvLen = 0;

            yuvLen.yWidth = 0;
            yuvLen.uWidth = 0;
            yuvLen.vWidth = 0;
            yuvLen.uvWidth = 0;
        }

        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P){
            yuvLen.yWidth = w;
            yuvLen.uWidth = w / 2;
            yuvLen.vWidth = w / 2;
            yuvLen.uvWidth = 0;

            yuvLen.yHeight = h;
            yuvLen.uHeight = h / 2;
            yuvLen.vHeight = h / 2;
            yuvLen.uvHeight = 0;           
        }

        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVNV12){
            yuvLen.yWidth = w;
            yuvLen.uWidth = 0;
            yuvLen.vWidth = 0;
            yuvLen.uvWidth = w;

            yuvLen.yHeight = h;
            yuvLen.uHeight = 0;
            yuvLen.vHeight = 0;
            yuvLen.uvHeight = h / 2;           
        }

        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVNV21){
            yuvLen.yWidth = w;
            yuvLen.uWidth = 0;
            yuvLen.vWidth = 0;
            yuvLen.uvWidth = w;

            yuvLen.yHeight = h;
            yuvLen.uHeight = 0;
            yuvLen.vHeight = 0;
            yuvLen.uvHeight = h / 2;           
        }

        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV422P){
            yuvLen.yWidth = w;
            yuvLen.uWidth = w / 2;
            yuvLen.vWidth = w / 2;
            yuvLen.uvWidth = 0;

            yuvLen.yHeight = h;
            yuvLen.uHeight = h;
            yuvLen.vHeight = h;
            yuvLen.uvHeight = 0;   
        }


        if(format == EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV444P){
            yuvLen.yWidth = w;
            yuvLen.uWidth = w;
            yuvLen.vWidth = w;
            yuvLen.uvWidth = 0;

            yuvLen.yHeight = h;
            yuvLen.uHeight = h;
            yuvLen.vHeight = h;
            yuvLen.uvHeight = 0;
        }


        yuvLen.yLen     = yuvLen.yWidth     *   yuvLen.yHeight;
        yuvLen.uLen     = yuvLen.uWidth     *   yuvLen.uHeight;
        yuvLen.vLen     = yuvLen.vWidth     *   yuvLen.vHeight;
        yuvLen.uvLen    = yuvLen.uvWidth    *   yuvLen.uvHeight; 

        return 0;
    }
}
