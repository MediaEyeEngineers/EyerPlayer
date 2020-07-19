#include "EyerTime.hpp"

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

namespace Eyer
{
    long long EyerTime::GetTime()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);

        return tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }

    EyerString EyerTime::TimeFormat()
    {
        char now[64];
        time_t tt;
        struct tm *ttime;

        time(&tt);

        ttime = localtime(&tt);
        strftime(now,64,"%Y-%m-%d %H:%M:%S",ttime);

        return EyerString(now);
    }

    int EyerTime::EyerSleep(int time)
    {
#ifdef _MSC_VER
        Sleep(time);
#else
        usleep(time);
#endif // _MSC_VER
        return 0;
    }
}