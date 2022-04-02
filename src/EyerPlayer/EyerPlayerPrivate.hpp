#ifndef EYERCAMERA_EYERPLAYERPRIVATE_HPP
#define EYERCAMERA_EYERPLAYERPRIVATE_HPP

#include <thread>
#include <mutex>

#include "ThreadReader.hpp"
#include "ThreadPlayCtr.hpp"
#include "EventControlThread.hpp"

namespace Eyer
{
    class EyerPlayerPrivate
    {
    public:
        EyerString url;
        std::mutex mut;
        EventControlThread * threadEventLoop = nullptr;
    };
}

#endif //EYERCAMERA_EYERPLAYERPRIVATE_HPP
