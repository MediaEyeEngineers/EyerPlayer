#include "signalplayer.h"
#include <QDebug>
#include <QTimer>
#include <QLCDNumber>

signalPlayer::signalPlayer(QObject *p): QObject(p)
{

}



void signalPlayer::openFile(QObject *p){

}

void signalPlayer::play(QObject *p){
    if(typeid (*p) == typeid (QLCDNumber)){
        QLCDNumber *fp = (QLCDNumber*) p;
        fp->setDigitCount(7);

        fp->setStyleSheet("border: 1px solid green; color: green; background: silver;");// 设置样式
        fp->display(0);
        qDebug() << "typeid (*p) == typeid (QLCDNumber)";
        pTimer = new QTimer(this);
        pTimer->setInterval(1000);
        connect(pTimer, &QTimer::timeout, this, [=](){
            fp->display(fp->value()+1);
            //std::cout << "playing : m_pTimer=> " << fp->value() << std::endl;
        });
        pTimer->start();
    }

}

void signalPlayer::stop(){

    if(pTimer != nullptr){

        pTimer->stop();
    }

}

void signalPlayer::conninuePlay(){
    if(pTimer != nullptr){
        pTimer->start();
    }
}

void signalPlayer::close(){
    if(pTimer != nullptr){
        stop();
        delete pTimer;
        pTimer = nullptr;
    }
}
