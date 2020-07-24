#ifndef	EYER_PLAYER_PRIVATE_H
#define	EYER_PLAYER_PRIVATE_H

#include "EyerPlayerEventManager.hpp"
#include <string>

namespace EyerPlayer 
{
    class EyerPlayerPrivate 
    {
    public:
        EyerPlayerEventManager * eventManager = nullptr;
        std::string url;
    };
}

#endif