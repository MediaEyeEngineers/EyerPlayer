#ifndef EYERLIB_MP4BOXSTSD_HPP
#define EYERLIB_MP4BOXSTSD_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"
#include "MP4BoxSampleEntry.hpp"

namespace Eyer
{
    class MP4BoxSTSD : public MP4FullBox {
    public:
        MP4BoxSTSD();
        ~MP4BoxSTSD();

        bool operator == (const MP4BoxSTSD & stsd) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        std::vector<MP4BoxSampleEntry *> sampleList;
        EyerBuffer stsdBuffer;
    };
}

#endif //EYERLIB_MP4BOXSTSD_HPP
