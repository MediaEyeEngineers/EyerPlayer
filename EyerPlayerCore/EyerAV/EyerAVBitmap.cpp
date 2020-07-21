//
// Created by redknot on 2020/1/5.
//

#include "EyerAVAV.hpp"

namespace Eyer
{
    EyerAVBitmap::EyerAVBitmap()
    {

    }

    EyerAVBitmap::~EyerAVBitmap()
    {
        if(pixelData != nullptr){
            free(pixelData);
            pixelData = nullptr;
        }
    }

    int EyerAVBitmap::SetRGBA8888(int w, int h, unsigned char * _pixelData)
    {
        if(pixelData != nullptr){
            free(pixelData);
            pixelData = nullptr;
        }

        format = EyerAVBitmapFormat::BITMAP_FORMAT_RGBA8888;

        SetW(w);
        SetH(h);

        int pixelDataLen = w * h * 4;
        pixelData = (unsigned char *)malloc(pixelDataLen);
        memcpy(pixelData, _pixelData, pixelDataLen);

        return 0;
    }

    EyerAVBitmapFormat EyerAVBitmap::GetFormat()
    {
        return format;
    }

    int EyerAVBitmap::GetW()
    {
        return width;
    }

    int EyerAVBitmap::GetH()
    {
        return height;
    }

    int EyerAVBitmap::SetW(int w)
    {
        width = w;
        return 0;
    }

    int EyerAVBitmap::SetH(int h)
    {
        height = h;
        return 0;
    }
}
