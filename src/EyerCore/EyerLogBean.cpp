#include "EyerLogBean.hpp"

namespace Eyer
{
    EyerLogBean::EyerLogBean(const char * _file, const char * _function, int _line, int _level, const char * _log)
    {
        file        = _file;
        function    = _function;
        line        = _line;
        log         = _log;
        logLevel    = _level;

        time_t t;
        struct tm * lt;
        time (&t);
        lt = localtime (&t);

        char timeStr[128];
        sprintf(timeStr, "%d-%02d-%02d %02d:%02d:%02d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
        timeS = timeStr;
    }

    EyerLogBean::~EyerLogBean()
    {

    }

    EyerLogBean::EyerLogBean(const EyerLogBean & log)
    {
        *this = log;
    }

    EyerLogBean & EyerLogBean::operator = (const EyerLogBean & logBean)
    {
        log         = logBean.log;
        file        = logBean.file;
        function    = logBean.function;
        line        = logBean.line;
        return *this;
    }

    EyerString & EyerLogBean::GetFile()
    {
        return file;
    }

    EyerString & EyerLogBean::GetFunction()
    {
        return function;
    }

    EyerString & EyerLogBean::GetLog()
    {
        return log;
    }

    int EyerLogBean::GetLevel()
    {
        return logLevel;
    }

    int EyerLogBean::GetLine()
    {
        return line;
    }

    EyerString & EyerLogBean::GetTimeStr()
    {
        return timeS;
    }
}