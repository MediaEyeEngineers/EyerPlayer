#ifndef EYERPLAYER_QUEUEBOX_HPP
#define EYERPLAYER_QUEUEBOX_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThreadHeader.hpp"
#include "EyerAV/EyerAV.hpp"

#include "EyerDecodeQueue/EyerDecodeQueueHeader.hpp"

namespace Eyer
{
    class QueueBox
    {
    public:
        QueueBox();
        ~QueueBox();

        int AddStream(const EyerAVStream & stream);
        int StartDeocder();
        int StopDecoder();

        bool IsStart();

        int GetPacketQueueCacheSize();
        int PutPacket(EyerAVPacket * packet);

        EyerDeocdeQueue * GetDeocdeQueue(int streamIndex);

        EyerObserverQueue<EyerAVFrame *> * GetOutputQueue();
        EyerConditionVariableBox cvBox;

    private:
        std::vector<EyerAVStream> streamList;
        std::vector<EyerDeocdeQueue *> decoderQueueList;
        EyerObserverQueue<EyerAVFrame *> outputQueue;

        std::atomic<bool> isStart {false};
    };
}

#endif //EYERPLAYER_QUEUEBOX_HPP
