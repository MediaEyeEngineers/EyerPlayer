#ifndef EYERLIB_MP4BOXHDLR_HPP
#define EYERLIB_MP4BOXHDLR_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxHDLR : public MP4FullBox {
    public:
        MP4BoxHDLR();
        ~MP4BoxHDLR();

        // MP4BoxHDLR & operator = (const MP4BoxHDLR & hdlr);
        bool operator == (const MP4BoxHDLR & hdlr) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        uint8_t handle_type_a = 0;
        uint8_t handle_type_b = 0;
        uint8_t handle_type_c = 0;
        uint8_t handle_type_d = 0;

        EyerString str;
    };
}



#endif //EYERLIB_MP4BOXHDLR_HPP
