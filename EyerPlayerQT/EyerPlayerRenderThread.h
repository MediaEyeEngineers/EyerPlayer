#ifndef EYERPLAYERRENDERTHREAD_H
#define EYERPLAYERRENDERTHREAD_H

#include <QObject>
#include <QThread>
#include <EyerPlayer/EyerPlayer.hpp>

class EyerPlayerRenderThread : public QThread
{
    Q_OBJECT
public:
    explicit EyerPlayerRenderThread(Eyer::EyerPlayer * _eyerPlayer);
    ~EyerPlayerRenderThread();

    int Stop();

protected:
    void run();

    std::atomic_int stopFlag {0};

signals:
    void RenderFrame(void * frame);

private:
    Eyer::EyerPlayer * eyerPlayer = nullptr;
};

#endif // EYERPLAYERRENDERTHREAD_H
