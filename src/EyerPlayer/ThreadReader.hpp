#ifndef EYERCAMERA_THREADREADER_HPP
#define EYERCAMERA_THREADREADER_HPP

#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class ThreadReader : public EyerThread
    {
    public:
        virtual void Run() override;
    };
}

#endif //EYERCAMERA_THREADREADER_HPP
