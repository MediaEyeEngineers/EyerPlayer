#ifndef EYERPLAYEREVENTMANAGER_H
#define EYERPLAYEREVENTMANAGER_H

#include <QThread>
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerPlayerThread.hpp"
#include "EyerPlayerLib.h"
#include "PlayerTypedef.hpp"

namespace EyerPlayer {
    /**
     * @brief EyerPlayerEventManager 是一个事件管理机
     * EyerPlayerEventManager 用来协调事件，核心是一个加锁的队列，各个线程投入或者取出事件，因为涉及到平台相关的回调（例如更新到 UI 界面）这个线程使用平台相关的线程实现，Qt 中就是 QThread
     */
    class EyerPlayerEventManager : public QThread
    {
        Q_OBJECT
    public:
        EyerPlayerEventManager(AVFrameQueueManager * queueManager);
        ~EyerPlayerEventManager();

        virtual void run();

        int Stop();

        int PushEvent(Eyer::EyerEvent * event);

        long long GenId();

    signals:
        void onOpen(int status, long long requestId, MediaInfo * info);
        void onStop(int status, long long requestId);
        void onUpdateUI(int streamId, void * frame);
        void onProgress(double playTime);

    public:
        Eyer::EyerEventQueue * eventQueue = nullptr;
    private:
        AVFrameQueueManager * queueManager = nullptr;

        AVReaderThread * readerThread = nullptr;

        std::atomic_int stopFlag {0};
        std::atomic_int isRun {0};
    };
}

#endif // EYERPLAYEREVENTMANAGER_H
