#include "EyerLogThread.hpp"
#include "EyerTime.hpp"

#include "EyerLog.hpp"
#include "eyer_log_thread_flag.hpp"

namespace Eyer
{
    int EyerLogThread::eyer_log_thread_flag = 1;
    EyerLogThread * EyerLogThread::instance = nullptr;

    EyerLogThread::GarbageCollector EyerLogThread::gc;

    EyerLogThread * EyerLogThread::GetInstance()
    {
        if(EyerLogThread::instance == nullptr){
            EyerLogThread::instance = new EyerLogThread();
            if(eyer_log_thread_flag){
                EyerLogThread::instance->Start();
            }
        }
        return EyerLogThread::instance;
    }

    EyerLogThread::EyerLogThread()
    {
    }

    EyerLogThread::~EyerLogThread()
    {
        while(logQueue.Size() > 0){
            EyerLogBean * logBean = nullptr;
            logQueue.FrontPop(logBean);
            if(logBean != nullptr){
                delete logBean;
                logBean = nullptr;
            }
        }
        logQueue.RemoveObserver(this);
    }

    int EyerLogThread::BeforeStop()
    {
        return 0;
    }

    void EyerLogThread::Run()
    {
        while(!stopFlag){
            EventLoop();
            while(logQueue.Size() <= 0 && !stopFlag){
                EventLoop();
                std::unique_lock<std::mutex> lck(cvMtx);
                cv.wait_for(lck, std::chrono::milliseconds(500));
            }

            while(logQueue.Size() > 0){
                EyerLogBean * logBean = nullptr;
                logQueue.FrontPop(logBean);
                if(logBean != nullptr){
                    if(logBean->GetLevel() >= level){
                        PrintLog(logBean);
                    }
                    delete logBean;
                    logBean = nullptr;
                }
            }
        }

        while(logQueue.Size() > 0){
            EyerLogBean * logBean = nullptr;
            logQueue.FrontPop(logBean);
            if(logBean != nullptr){
                if(logBean->GetLevel() >= level){
                    PrintLog(logBean);
                }

                delete logBean;
                logBean = nullptr;
            }
        }
    }

    int EyerLogThread::Update()
    {
        cv.notify_one();
        return 0;
    }

    int EyerLogThread::Clear()
    {
        while(logQueue.Size() > 0){
            EyerLogBean * logBean = nullptr;
            logQueue.FrontPop(logBean);
            if(logBean != nullptr){
                if(logBean->GetLevel() >= level){
                    PrintLog(logBean);
                }
                delete logBean;
                logBean = nullptr;
            }
        }

        return 0;
    }

    int EyerLogThread::SetPath(const EyerString & _path)
    {
        path = _path;
        return 0;
    }

    int EyerLogThread::SetParam(EyerLogParam & _param)
    {
        param = _param;
        return 0;
    }

    int EyerLogThread::PrintLog(EyerLogBean * logBean)
    {
        std::string logstr;
        if(param.isLevel){
            char levelStr[8];
            sprintf(levelStr, "[%2d] ", logBean->GetLevel());
            logstr += levelStr;
        }
        if(param.isTime){
            logstr += "[" + std::string(logBean->GetTimeStr().str) + "] ";
        }
        if(param.isFile){
            logstr += "[" + std::string(logBean->GetFile().str) + "(" + std::to_string(logBean->GetLine()) + ")" + "] ";
        }
        if(param.isFunc){
            logstr += "[" + std::string(logBean->GetFunction().str) + "] ";
        }
        logstr += std::string(logBean->GetLog().str);

        if(path.IsEmpty()){
            printf("%s", logstr.c_str());
            fflush(stdout);
            fflush(stderr);
        }
        else{
            FILE * f = fopen(path.str, "at+");
            if(f != nullptr){
                fprintf(f, "%s", logstr.c_str());
                fflush(f);
                fclose(f);
            }
        }

        return 0;
    }

    int EyerLogThread::PutLog(EyerLogBean * logBean)
    {
        if(eyer_log_thread_flag){
            logQueue.Push(logBean);
        }
        else{
            if(logBean != nullptr){
                PrintLog(logBean);
                delete logBean;
            }
        }

        return 0;
    }

    int EyerLogThread::SetLevel(int _level)
    {
        level = _level;
        return 0;
    }
}