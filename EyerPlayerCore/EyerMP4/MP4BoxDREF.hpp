#ifndef EYERLIB_MP4BOXDREF_HPP
#define EYERLIB_MP4BOXDREF_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxDREF  : public MP4FullBox {
    public:
        MP4BoxDREF();
        ~MP4BoxDREF();

        bool operator == (const MP4BoxDREF & dinf) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        EyerBuffer drefBuffer;
    };
}

#endif //EYERLIB_MP4BOXDREF_HPP
