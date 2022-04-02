#ifndef EYERPLAYER_EYERPLAYERCONTEXT_HPP
#define EYERPLAYER_EYERPLAYERCONTEXT_HPP

#include <mutex>

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerPlayerContext
    {
    public:
        EyerPlayerContext();
        ~EyerPlayerContext();

        EyerString url;
        std::mutex commonMut;
    };
}

#endif //EYERPLAYER_EYERPLAYERCONTEXT_HPP
