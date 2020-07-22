#ifndef	EYER_PLAYER_PRIVATE_H
#define	EYER_PLAYER_PRIVATE_H

#include "EventManager.hpp"

namespace Eyer 
{
    class EyerPlayerPrivate 
    {
    public:
        EyerPlayerEventManager * eventManager = nullptr;
    };
}

#endif