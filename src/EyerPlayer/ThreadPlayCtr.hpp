#ifndef EYERCAMERA_THREADPLAYCTR_HPP
#define EYERCAMERA_THREADPLAYCTR_HPP

#include "EyerThread/EyerThread.hpp"
#include "QueueBox.hpp"

namespace Eyer
{
    class ThreadEventLoop;

    enum class PLAY_CTR_STATUS
    {
        PLAYING,
        PAUSEING
    };

    class ThreadPlayCtr : public EyerThread
    {
    public:
        ThreadPlayCtr(QueueBox * _queueBox, ThreadEventLoop * _eventLoop);
        ~ThreadPlayCtr();

        void Run_();
        virtual void Run() override;
        virtual int SetStopFlag() override;
        virtual int SetStartEventLoopFlag() override;

        int Pause();
        int Resume();
    private:
        ThreadEventLoop * eventLoop = nullptr;
        QueueBox * queueBox = nullptr;

        EyerAVFrame * GetFrameFromDecodeQueue(int streamId);

        PLAY_CTR_STATUS status = PLAY_CTR_STATUS::PLAYING;

        long long startTime = -1;
        double dTime = 0.0;
        double pausedTime = 0.0;
    };
}

#endif //EYERCAMERA_THREADPLAYCTR_HPP
