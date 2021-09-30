#ifndef EYERCAMERA_EYERPLAYERPRIVATE_HPP
#define EYERCAMERA_EYERPLAYERPRIVATE_HPP

#include <thread>
#include <mutex>

#include "ThreadReader.hpp"
#include "ThreadPlayCtr.hpp"

namespace Eyer
{
    class EyerPlayerPrivate
    {
    public:
        std::mutex mut;
        ThreadReader * threadReader = nullptr;
        ThreadPlayCtr * threadPlayCtr = nullptr;
    };
}

#endif //EYERCAMERA_EYERPLAYERPRIVATE_HPP
