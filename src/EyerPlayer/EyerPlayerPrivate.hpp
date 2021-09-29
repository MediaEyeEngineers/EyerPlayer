#ifndef EYERCAMERA_EYERPLAYERPRIVATE_HPP
#define EYERCAMERA_EYERPLAYERPRIVATE_HPP

#include <thread>
#include <mutex>

#include "ThreadReader.hpp"

namespace Eyer
{
    class EyerPlayerPrivate
    {
    public:
        std::mutex mut;
        ThreadReader * threadReader = nullptr;
    };
}

#endif //EYERCAMERA_EYERPLAYERPRIVATE_HPP
