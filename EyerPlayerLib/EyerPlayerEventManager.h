#ifndef EYERPLAYEREVENTMANAGER_H
#define EYERPLAYEREVENTMANAGER_H

#include <QThread>
#include "EyerEventQueue/EyerEventQueue.hpp"
#include "EyerPlayerThread.hpp"
#include "EyerPlayerLib.h"
#include "PlayerTypedef.hpp"

namespace EyerPlayer {
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
        void onOpen(int status, long long requestId);
        void onStop(int status, long long requestId);
        void onUpdateUI(int streamId, void * frame);

    public:
        Eyer::EyerEventQueue * eventQueue = nullptr;
    private:
        AVFrameQueueManager * queueManager = nullptr;


        PlayCtrThread * playCtrThread = nullptr;
        AVReaderThread * readerThread = nullptr;

        std::atomic_int stopFlag {0};
        std::atomic_int isRun {0};
    };
}

#endif // EYERPLAYEREVENTMANAGER_H
