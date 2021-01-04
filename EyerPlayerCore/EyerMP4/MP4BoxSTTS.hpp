#ifndef EYERLIB_MP4BOXSTTS_HPP
#define EYERLIB_MP4BOXSTTS_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxSTTSSample
    {
    public:
        uint32_t sample_count = 0;
        uint32_t sample_delta = 0;
    };

    class MP4BoxSTTS : public MP4FullBox{
    public:
        MP4BoxSTTS();
        ~MP4BoxSTTS();

        bool operator == (const MP4BoxSTTS & stts) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        std::vector<MP4BoxSTTSSample *> sampleList;
    };
}

#endif //EYERLIB_MP4BOXSTTS_HPP
