#ifndef EYERCAMERA_THREADPLAYCTR_HPP
#define EYERCAMERA_THREADPLAYCTR_HPP

#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class ThreadEventLoop;

    class ThreadPlayCtr : public EyerThread
    {
    public:
        ThreadPlayCtr(ThreadEventLoop * _eventLoop);
        ~ThreadPlayCtr();

        virtual void Run() override;

    private:
        ThreadEventLoop * eventLoop = nullptr;
    };
}

#endif //EYERCAMERA_THREADPLAYCTR_HPP
