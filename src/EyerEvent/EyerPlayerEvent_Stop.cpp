#include "EyerPlayerEvent_Stop.hpp"

namespace Eyer
{
    EyerPlayerEvent_Stop::EyerPlayerEvent_Stop()
    {
        type = EventType::STOP_REQUEST;
    }

    EyerPlayerEvent_Stop::~EyerPlayerEvent_Stop()
    {

    }
}