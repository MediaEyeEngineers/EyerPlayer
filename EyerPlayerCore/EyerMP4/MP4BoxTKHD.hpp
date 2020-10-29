#ifndef EYERLIB_MP4BOXTKHD_HPP
#define EYERLIB_MP4BOXTKHD_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxTKHD : public MP4FullBox {
    public:
        MP4BoxTKHD();
        ~MP4BoxTKHD();

        bool operator == (const MP4BoxTKHD & tkhd) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        uint64_t creation_time = 0;
        uint64_t modification_time = 0;
        uint32_t track_ID = 0;
        uint64_t duration = 0;

        uint16_t layer = 0;
        uint16_t alternate_group = 0;

        float volume = 0.0f;

        float matrix[9] = {0};

        uint32_t width = 0.0f;
        uint32_t height = 0.0f;
    };
}

#endif //EYERLIB_MP4BOXTKHD_HPP
