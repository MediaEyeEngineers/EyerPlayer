#ifndef SIGNALPLAYER_H
#define SIGNALPLAYER_H



#include <QObject>
#include <QWidget>

class signalPlayer:public QObject
{

public:
    signalPlayer(QObject *p = nullptr);


    void openFile(QObject *p);
    void play(QObject *p);
    void stop();
    void conninuePlay();
    void close();
QTimer *pTimer = nullptr;
private:

};

#endif // SIGNALPLAYER_H
