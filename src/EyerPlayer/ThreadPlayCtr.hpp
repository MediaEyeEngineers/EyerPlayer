#ifndef EYERCAMERA_THREADPLAYCTR_HPP
#define EYERCAMERA_THREADPLAYCTR_HPP

#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class ThreadPlayCtr : public EyerThread
    {
    public:
        virtual void Run() override;
    };
}

#endif //EYERCAMERA_THREADPLAYCTR_HPP
