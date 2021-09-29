#include "EyerLog.hpp"

#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <stdarg.h>

#include "EyerLogThread.hpp"
#include "EyerLogBean.hpp"
#include "eyer_log_thread_flag.hpp"

int eyer_log_path(const char * path)
{
    Eyer::EyerLogThread * logThread = Eyer::EyerLogThread::GetInstance();
    return logThread->SetPath(path);
}

int eyer_log_set_level(int level)
{
    Eyer::EyerLogThread * logThread = Eyer::EyerLogThread::GetInstance();
    logThread->SetLevel(level);
    return 0;
}

int eye_log_set_level(int level)
{
    Eyer::EyerLogThread * logThread = Eyer::EyerLogThread::GetInstance();
    logThread->SetLevel(level);
    return 0;
}

int eyer_log_param (int isLevel, int isTime, int isFile, int isLine, int isFunc)
{
    Eyer::EyerLogParam param;
    param.isLevel = isLevel;
    param.isTime = isTime;
    param.isFunc = isFunc;
    param.isFile = isFile;
    param.isLine = isLine;

    Eyer::EyerLogThread * logThread = Eyer::EyerLogThread::GetInstance();
    logThread->SetParam(param);

    return 0;
}

void     eyer_log_thread             (int thread)
{
    Eyer::EyerLogThread::eyer_log_thread_flag = thread;
}

void eyer_log_log(const char * file, const char * function, int line, int level, const char * format, ...)
{
    char logStr[4096];
    memset(logStr, 0, 4096);

    va_list args;
    va_start(args, format);
    vsnprintf(logStr, 4096, format, args);
    va_end(args);

    Eyer::EyerLogBean * logBean = new Eyer::EyerLogBean(file, function, line, level, logStr);

    Eyer::EyerLogThread * logThread = Eyer::EyerLogThread::GetInstance();
    logThread->PutLog(logBean);
}

int     eyer_log_clear          ()
{
    class ClearEyerRunnable : public Eyer::EyerRunnable
    {
    public:
        ClearEyerRunnable(Eyer::EyerLogThread * _logThread)
        {
            logThread = _logThread;
        }

        virtual void Run()
        {
            logThread->Clear();
        }
    private:
        Eyer::EyerLogThread * logThread = nullptr;
    };

    Eyer::EyerLogThread * logThread = Eyer::EyerLogThread::GetInstance();

    ClearEyerRunnable clearRunnable(logThread);

    logThread->PushEvent(&clearRunnable);
    logThread->StartEventLoop();
    logThread->StopEventLoop();

    return 0;
}