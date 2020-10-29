#ifndef EYERLIB_MP4BOXAVCC_HPP
#define EYERLIB_MP4BOXAVCC_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxAVCC : public MP4Box {
    public:
        MP4BoxAVCC();
        ~MP4BoxAVCC();

        bool operator == (const MP4BoxAVCC & avcc) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        uint8_t configurationVersion = 0;
        uint8_t AVCProfileIndication = 0;
        uint8_t profile_compatibility = 0;
        uint8_t AVCLevelIndication = 0;
        uint8_t lengthSizeMinusOne = 0;

        std::vector<EyerBuffer *> spsList;
        std::vector<EyerBuffer *> ppsList;

        uint8_t chroma_format = 0;
        uint8_t bit_depth_luma_minus8 = 0;
        uint8_t bit_depth_chroma_minus8 = 0;
        std::vector<EyerBuffer *> spsExtList;
    };
}

#endif //EYERLIB_MP4BOXAVCC_HPP
