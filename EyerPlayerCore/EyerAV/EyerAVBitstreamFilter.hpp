#ifndef EYE_LIB_EYERAVBITSTREAMFILTER_HPP
#define EYE_LIB_EYERAVBITSTREAMFILTER_HPP

#include "EyerAVAV.hpp"

namespace Eyer {

    class EyerAVBitstreamFilterPrivate;

    enum EyerAVBitstreamFilterType
    {
        h264_mp4toannexb = 1,
        hevc_mp4toannexb = 2
    };

    class EyerAVBitstreamFilter {
    public:
        EyerAVBitstreamFilter(EyerAVBitstreamFilterType type, EyerAVStream & stream);
        ~EyerAVBitstreamFilter();

        int SendPacket(EyerAVPacket * packet);
        int ReceivePacket(EyerAVPacket * packet);

        static int QueryAllBitstreamFilter();
    private:
        EyerAVBitstreamFilterPrivate * piml = nullptr;
    };
}

#endif //EYE_LIB_EYERAVBITSTREAMFILTER_HPP
