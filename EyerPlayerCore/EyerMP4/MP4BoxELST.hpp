#ifndef EYERLIB_MP4BOXELST_HPP
#define EYERLIB_MP4BOXELST_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxELSTEntry
    {
    public:
        uint64_t segment_duration;
        int64_t  media_time;
        float media_rate;
    };

    class MP4BoxELST : public MP4FullBox {
    public:
        MP4BoxELST();
        ~MP4BoxELST();

        bool operator == (const MP4BoxELST & elst) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        std::vector<MP4BoxELSTEntry> entryList;
    };
}

#endif //EYERLIB_MP4BOXELST_HPP
