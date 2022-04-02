#include "EyerPlayerEvent_Play.hpp"

namespace Eyer
{
    EyerPlayerEvent_Play::EyerPlayerEvent_Play()
    {
        type = EventType::PLAY_REQUEST;
    }

    EyerPlayerEvent_Play::~EyerPlayerEvent_Play()
    {

    }
}