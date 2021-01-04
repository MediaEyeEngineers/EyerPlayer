#ifndef EYERLIB_MP4BOXMVHD_HPP
#define EYERLIB_MP4BOXMVHD_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxMVHD : public MP4FullBox {
    public:
        MP4BoxMVHD();
        ~MP4BoxMVHD();

        bool operator == (const MP4BoxMVHD & mvhd) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    public:
        uint64_t creation_time = 0;
        uint64_t modification_time = 0;
        uint32_t timescale = 0;
        uint64_t duration = 0;

        float rate;
        float volume;

        float matrix[9] = {0};

        uint32_t next_track_ID;
    };
}



#endif //EYERLIB_MP4BOXMVHD_HPP
