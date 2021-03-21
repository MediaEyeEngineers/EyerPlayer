#include "signalplayer.h"
#include "winopenglwidget.h"
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
        fp->display(0.0);
        qDebug() << "typeid (*p) == typeid (QLCDNumber)";
        m_pTimer = new QTimer(this);
        m_pTimer->setInterval(100);
        connect(m_pTimer, &QTimer::timeout, this, [=](){
            fp->display(fp->value()+0.1);
            std::cout << "playing : m_pTimer=> " << fp->value() << std::endl;
        });
        m_pTimer->start();
    }

}

void signalPlayer::stop(){
    if(m_pTimer != nullptr){
        m_pTimer->stop();
    }

}

void signalPlayer::conninuePlay(){
    if(m_pTimer != nullptr){
        m_pTimer->start();
    }
}

void signalPlayer::close(){
    if(m_pTimer != nullptr){
        stop();
        delete m_pTimer;
        m_pTimer = nullptr;
    }
}
