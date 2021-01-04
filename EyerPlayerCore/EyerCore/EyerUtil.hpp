#ifndef EYERLIB_EYERUTIL_HPP
#define EYERLIB_EYERUTIL_HPP

#include <stdint.h>
#include "EyerCore.hpp"

namespace Eyer
{
    class EyerUtil {
    public:
        static uint64_t EndianNtohll        (uint64_t val);
        static uint32_t EndianNtohl         (uint32_t val);
        static uint16_t EndianNtohs         (uint16_t val);

        static uint64_t EndianHtonll        (uint64_t val);
        static uint32_t EndianHtonl         (uint32_t val);
        static uint16_t EndianHtons         (uint16_t val);

        static bool CheckCPU();

        static EyerString Md5(const EyerString & messgae);
    };
}

#endif //EYERLIB_EYERUTIL_HPP
