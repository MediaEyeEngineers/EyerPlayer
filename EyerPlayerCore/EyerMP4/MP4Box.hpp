#ifndef EYERLIB_MP4BOX_HPP
#define EYERLIB_MP4BOX_HPP

#include <stdint.h>
#include <vector>
#include <string.h>
#include "BoxType.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class MP4Box {
    public:
        MP4Box();
        MP4Box(BoxType type);
        MP4Box(const MP4Box & box);
        virtual ~MP4Box();


        MP4Box & operator = (const MP4Box & box);
        bool operator == (const MP4Box & box) const;

        // <===Serialize===>
        EyerBuffer Serialize();
        EyerBuffer SerializeSubBox();
        virtual EyerBuffer SerializeParam();
        // <===Serialize===>

        // <===Parse===>
        int Parse(EyerBuffer & buffer);
        int ParseSubBox(EyerBuffer & buffer, int offset = 0);
        virtual int ParseParam(EyerBuffer & buffer, int offset);
        // <===Parse===>

        int AddSubBox(MP4Box * box);
        int AddSubBox(MP4Box & box);

        uint64_t GetSize();

        BoxType GetType();


        MP4Box * GetSubBoxPtr(BoxType type);


        virtual int PrintInfo(int level = 0);



        static MP4Box * CreatBox(BoxType type);
        static MP4Box * CopyBox(MP4Box * box);

    protected:
        uint64_t size = 0;
        BoxType type;

        std::vector<MP4Box *> subBoxList;
    };
}

#endif //EYERLIB_MP4BOX_HPP
