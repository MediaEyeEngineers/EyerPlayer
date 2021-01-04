#ifndef EYERLIB_MP4BOXSTCO_HPP
#define EYERLIB_MP4BOXSTCO_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxSTCO : public MP4FullBox{
    public:
        MP4BoxSTCO();
        ~MP4BoxSTCO();

        bool operator == (const MP4BoxSTCO & stco) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        std::vector<uint32_t> chunk_offset_list;
    };
}

#endif //EYERLIB_MP4BOXSTCO_HPP
