#ifndef EYERLIB_MP4BOXMDHD_HPP
#define EYERLIB_MP4BOXMDHD_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer {
    class MP4BoxMDHD : public MP4FullBox {
    public:
        MP4BoxMDHD();
        ~MP4BoxMDHD();

        bool operator == (const MP4BoxMDHD & mdhd) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        uint64_t creation_time = 0;
        uint64_t modification_time = 0;
        uint32_t time_scale = 0;
        uint64_t duration;
    };
}


#endif //EYERLIB_MP4BOXMDHD_HPP
