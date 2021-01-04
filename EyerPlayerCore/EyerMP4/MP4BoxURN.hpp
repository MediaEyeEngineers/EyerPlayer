#ifndef EYERLIB_MP4BOXURN_HPP
#define EYERLIB_MP4BOXURN_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxURN : public MP4FullBox{
    public:
        MP4BoxURN();
        ~MP4BoxURN();

        bool operator == (const MP4BoxURN & urn) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();
    };
}

#endif //EYERLIB_MP4BOXURN_HPP
