#ifndef EYERLIB_MP4BOXTREX_HPP
#define EYERLIB_MP4BOXTREX_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxTREX : public MP4FullBox {
    public:
        MP4BoxTREX();
        ~MP4BoxTREX();

        bool operator == (const MP4BoxTREX & trex) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    public:
        uint32_t track_ID = 0;
        uint32_t default_sample_description_index = 0;
        uint32_t default_sample_duration = 0;
        uint32_t default_sample_size = 0;
        uint32_t default_sample_flag = 0;
    };
}

#endif //EYERLIB_MP4BOXTREX_HPP
