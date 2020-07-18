#ifndef	EYER_CORE_TIME_H
#define	EYER_CORE_TIME_H

#include "EyerString.hpp"

#ifdef _MSC_VER
#include <winsock2.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif // _MSC_VER

namespace Eyer
{
    class EyerTime
    {
    public:
        static long long GetTime();
        static EyerString TimeFormat();

        static int EyerSleep(int time);
    };
}

#endif
