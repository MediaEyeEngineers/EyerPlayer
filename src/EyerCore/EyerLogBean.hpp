#ifndef EYERLIB_EYERLOGBEAN_HPP
#define EYERLIB_EYERLOGBEAN_HPP

#include "EyerString.hpp"
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <stdarg.h>

namespace Eyer
{
    class EyerLogBean {
    public:
        EyerLogBean(const char * _file, const char * _function, int _line, int _level, const char * _log);
        ~EyerLogBean();
        EyerLogBean(const EyerLogBean & log);
        EyerLogBean & operator = (const EyerLogBean & log);

        EyerString & GetFile();
        EyerString & GetFunction();
        EyerString & GetLog();
        EyerString & GetTimeStr();
        int GetLine();
        int GetLevel();

    private:
        int logLevel = 5;
        EyerString log;
        EyerString file;
        EyerString function;
        int line;
        EyerString timeS;
    };
}

#endif //EYERLIB_EYERLOGBEAN_HPP
