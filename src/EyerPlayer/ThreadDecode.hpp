#ifndef EYERCAMERA_THREADDECODE_HPP
#define EYERCAMERA_THREADDECODE_HPP

#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class ThreadDecode : public EyerThread
    {
    public:
        virtual void Run() override;
    };
}

#endif //EYERCAMERA_THREADDECODE_HPP
