#include "EyerISOTypeReader.hpp"

namespace Eyer
{
    double EyerISOTypeReader::ReadFixedPoint1616 (const uint8_t * data)
    {
        int result = 0;
        result |= ((data[0] << 24) & 0xFF000000);
        result |= ((data[1] << 16) & 0xFF0000);
        result |= ((data[2] << 8) & 0xFF00);
        result |= ((data[3]) & 0xFF);
        return ((double) result) / 65536;
    }

    float EyerISOTypeReader::ReadFixedPoint88 (const uint8_t * data)
    {
        short result = 0;
        result |= ((data[0] << 8) & 0xFF00);
        result |= ((data[1]) & 0xFF);
        return ((float) result) / 256;
    }
}
