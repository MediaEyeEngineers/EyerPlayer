#include "EyerTime.hpp"

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <chrono>

namespace Eyer
{
    long long EyerTime::GetTime()
    {
        /*
        struct timeval tv;
        gettimeofday(&tv, NULL);

        return tv.tv_sec * 1000 + tv.tv_usec / 1000;
        */

        std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	    return (long long)tmp.count();
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