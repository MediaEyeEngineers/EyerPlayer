#ifndef EYERPLAYER_EYERDEOCDEQUEUEFFMPEG_HPP
#define EYERPLAYER_EYERDEOCDEQUEUEFFMPEG_HPP

#include "EyerDeocdeQueue.hpp"
#include "EyerThread/EyerThreadHeader.hpp"

namespace Eyer
{
    class EyerDeocdeQueueFFmpeg : public EyerDeocdeQueue
    {
    public:
        EyerDeocdeQueueFFmpeg(const EyerAVStream & stream, EyerConditionVariableBox * _cvBox);
        ~EyerDeocdeQueueFFmpeg();

        virtual void Run() override;
        virtual int SetStopFlag() override;

        virtual int StartDecode() override;
        virtual int StopDecode() override;
    };
}

#endif //EYERPLAYER_EYERDEOCDEQUEUEFFMPEG_HPP
