#include "MP4FullBox.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4FullBox::MP4FullBox() : MP4Box()
    {

    }

    MP4FullBox::~MP4FullBox()
    {

    }

    bool MP4FullBox::operator == (const MP4FullBox & fullbox) const
    {
        if(version != fullbox.version){
            return false;
        }

        return true;
    }

    EyerBuffer MP4FullBox::SerializeParam()
    {
        EyerBuffer buffer;

        uint8_t h[4] = {0, 0, 0, 0};

        buffer.Append(h, 4);

        return buffer;
    }

    int MP4FullBox::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4Box::ParseParam(buffer, offset);

        unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
        buffer.GetBuffer(data);

        memcpy(&version, data + offset, 1);
        flags = 0;

        // printf("full box version: %d\n", version);

        free(data);
        return offset + 4;
    }

    int MP4FullBox::PrintInfo(int level)
    {
        MP4Box::PrintInfo(level);
        return 0;
    }
}