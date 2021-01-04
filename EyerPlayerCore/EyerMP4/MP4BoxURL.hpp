#ifndef EYERLIB_MP4BOXURL_HPP
#define EYERLIB_MP4BOXURL_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxURL : public MP4FullBox{
    public:
        MP4BoxURL();
        ~MP4BoxURL();

        bool operator == (const MP4BoxURL & url) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        EyerString location;
    };
}

#endif //EYERLIB_MP4BOXURL_HPP
