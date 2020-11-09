#ifndef EYERLIB_MP4BOXMFHD_HPP
#define EYERLIB_MP4BOXMFHD_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxMFHD : public MP4FullBox {
    public:
        MP4BoxMFHD();
        ~MP4BoxMFHD();

        bool operator == (const MP4BoxMFHD & mfhd) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();


        uint32_t Get_sequence_number();
        int Set_sequence_number(uint32_t sequence_number);

    private:
        uint32_t sequence_number = 0;
    };
}

#endif //EYERLIB_MP4BOXMFHD_HPP
