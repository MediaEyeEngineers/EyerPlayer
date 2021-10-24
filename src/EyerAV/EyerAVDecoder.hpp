#ifndef EYERLIB_EYERAVDECODER_HPP
#define EYERLIB_EYERAVDECODER_HPP

#include "EyerAVStream.hpp"
#include "EyerAVPacket.hpp"
#include "EyerAVFrame.hpp"

namespace Eyer
{
    class EyerAVDecoderPrivate;

    class EyerAVDecoder
    {
    public:
        EyerAVDecoder();
        ~EyerAVDecoder();

        int Init(EyerAVStream & stream);

        int GetTimebase(EyerAVRational & timebase);

        int SendPacket(EyerAVPacket * packet);
        int SendPacket(EyerAVPacket & packet);
        int SendPacket(EyerSmartPtr<EyerAVPacket> & packet);

        int SendPacketNull();
        int RecvFrame(EyerAVFrame & frame);
        EyerSmartPtr<EyerAVFrame> RecvFrame(int & ret);

    private:
        // 禁止拷贝
        EyerAVDecoder(const EyerAVDecoder &) = delete;
        EyerAVDecoder & operator = (const EyerAVDecoder &) = delete;

    public:
        EyerAVDecoderPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVDECODER_HPP
