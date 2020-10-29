#ifndef EYERLIB_MP4FULLBOX_HPP
#define EYERLIB_MP4FULLBOX_HPP

#include "MP4Box.hpp"

namespace Eyer
{
    class MP4FullBox : public MP4Box {
    public:
        MP4FullBox();
        ~MP4FullBox();

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        bool operator == (const MP4FullBox & fullbox) const;

    protected:
        uint8_t version = 0;
        uint32_t flags = 0;
    };
}

#endif //EYERLIB_MP4FULLBOX_HPP
