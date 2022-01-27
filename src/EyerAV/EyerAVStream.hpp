#ifndef EYERLIB_EYERAVSTREAM_HPP
#define EYERLIB_EYERAVSTREAM_HPP

#include <stdio.h>
#include "EyerAVCodecType.hpp"
#include "EyerAVCodecID.hpp"
#include "EyerAVRational.hpp"

namespace Eyer
{
    class EyerAVStreamPrivate;

    class EyerAVStream {
    public:
        EyerAVStream();
        ~EyerAVStream();

        EyerAVStream(const EyerAVStream & stream);
        EyerAVStream(EyerAVStream && stream);

        EyerAVStream & operator = (const EyerAVStream & stream);

        int GetStreamId();
        double GetDuration() const;

        EyerAVCodecType GetType();
        int GetWidth();
        int GetHeight();
        EyerAVCodecID GetCodecID();

        EyerAVRational GetTimebase();
    public:
        EyerAVStreamPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVSTREAM_HPP
