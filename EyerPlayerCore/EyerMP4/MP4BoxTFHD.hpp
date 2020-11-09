//
// Created by Administrator on 2020/11/3.
//

#ifndef EYERLIB_MP4BOXTFHD_HPP
#define EYERLIB_MP4BOXTFHD_HPP

#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxTFHD : public MP4FullBox {
    public:
        MP4BoxTFHD();
        ~MP4BoxTFHD();

        bool operator == (const MP4BoxTFHD & tfhd) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        uint32_t track_ID = 0;
        uint64_t base_data_offset = 0;
        uint32_t sample_description_index = 0;
        uint32_t default_sample_duration = 0;
        uint32_t default_sample_size = 0;
        uint32_t default_sample_flags = 0;
    };
}

#endif //EYERLIB_MP4BOXTFHD_HPP
