#include "EventManager.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerEventQueue/EyerEventQueue.hpp"

namespace Eyer 
{
    EyerPlayerEventManager::EyerPlayerEventManager()
    {
        eventQueue = new Eyer::EyerEventQueue();
    }

    EyerPlayerEventManager::~EyerPlayerEventManager()
    {
        if(eventQueue != nullptr){
            delete eventQueue;
            eventQueue = nullptr;
        }
    }

    void EyerPlayerEventManager::Run()
    {
        EyerLog("Event Manager Start\n");
        while(!stopFlag){
            Eyer::EyerTime::EyerSleep(1000);

            Eyer::EyerEvent * event = nullptr;
            eventQueue->FrontTargetAndPop(event, "");
            if(event != nullptr){
            }
        }
        EyerLog("Event Manager End\n");
    };
}