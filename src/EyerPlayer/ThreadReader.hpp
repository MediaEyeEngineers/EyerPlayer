#ifndef EYERCAMERA_THREADREADER_HPP
#define EYERCAMERA_THREADREADER_HPP

#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class ThreadEventLoop;

    class ThreadReader : public EyerThread
    {
    public:
        ThreadReader(ThreadEventLoop * _eventLoop);
        ~ThreadReader();

        virtual void Run() override;

    private:
        ThreadEventLoop * eventLoop = nullptr;
    };
}

#endif //EYERCAMERA_THREADREADER_HPP
