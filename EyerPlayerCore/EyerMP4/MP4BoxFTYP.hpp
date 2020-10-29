#ifndef EYERLIB_MP4BOXFTYP_HPP
#define EYERLIB_MP4BOXFTYP_HPP

#include "MP4Box.hpp"

namespace Eyer
{
    class MP4BoxFTYP : public MP4Box {
    public:
        MP4BoxFTYP();
        ~MP4BoxFTYP();

        bool operator == (const MP4BoxFTYP & ftyp) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();
    private:
        uint8_t major_brand[4];
        uint32_t minor_version = 0;

        int compatible_brands_len = 0;
        uint8_t compatible_brands[4][4];
    };
}



#endif //EYERLIB_MP4BOXFTYP_HPP
