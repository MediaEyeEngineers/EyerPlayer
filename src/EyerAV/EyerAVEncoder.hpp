#ifndef EYERLIB_EYERAVENCODER_HPP
#define EYERLIB_EYERAVENCODER_HPP

#include "EyerAVEncoderParam.hpp"

#include "EyerAVFrame.hpp"
#include "EyerAVPacket.hpp"
#include "EyerAVADTS.hpp"

namespace Eyer
{
    class EyerAVEncoderPrivate;

    class EyerAVEncoder {
    public:
        EyerAVEncoder();
        ~EyerAVEncoder();

        int Init(const EyerAVEncoderParam & param);

        int SendFrame(EyerAVFrame & frame);
        int SendFrameNull();
        int RecvPacket(EyerAVPacket & packet);

        int GetTimebase(EyerAVRational & timebase);

        EyerAVADTS GetADTS(int packetSize);

    private:
        EyerAVEncoder(const EyerAVEncoder & encoder) = delete;
        EyerAVEncoder & operator = (const EyerAVEncoder & encoder) = delete;

    public:
        EyerAVEncoderPrivate * piml = nullptr;
    };
}

#endif //EYERLIB_EYERAVENCODER_HPP
