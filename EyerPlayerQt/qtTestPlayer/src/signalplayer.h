#ifndef SIGNALPLAYER_H
#define SIGNALPLAYER_H

#include "winopenglwidget.h"

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

private:
    QTimer *m_pTimer = nullptr;
};

#endif // SIGNALPLAYER_H
