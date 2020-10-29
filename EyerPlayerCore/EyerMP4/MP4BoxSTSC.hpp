#ifndef EYERLIB_MP4BOXSTSC_HPP
#define EYERLIB_MP4BOXSTSC_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxSTSCChunk
    {
    public:
        uint32_t first_chunk = 0;
        uint32_t samples_per_chunk = 0;
        uint32_t sample_description_index = 0;
    };

    class MP4BoxSTSC : public MP4FullBox{
    public:
        MP4BoxSTSC();
        ~MP4BoxSTSC();

        bool operator == (const MP4BoxSTSC & stsc) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        std::vector<MP4BoxSTSCChunk *> chunkList;
    };
}

#endif //EYERLIB_MP4BOXSTSC_HPP
