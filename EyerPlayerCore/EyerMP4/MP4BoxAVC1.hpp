#ifndef EYERLIB_MP4BOXAVC1_HPP
#define EYERLIB_MP4BOXAVC1_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"
#include "MP4BoxSampleEntry.hpp"
#include "MP4BoxAVCC.hpp"

namespace Eyer
{
    class MP4BoxAVC1 : public MP4BoxSampleEntry {
    public:
        MP4BoxAVC1();
        ~MP4BoxAVC1();

        bool operator == (const MP4BoxAVC1 & dinf) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        uint16_t data_reference_index = 0;
        uint16_t width = 0;
        uint16_t height = 0;

        uint32_t horizresolution = 0;
        uint32_t vertresolution = 0;

        uint16_t frame_count = 0;

        EyerString compressorname;

        uint16_t depth = 0;


        MP4BoxAVCC avcc;
    };
}

#endif //EYERLIB_MP4BOXAVC1_HPP
