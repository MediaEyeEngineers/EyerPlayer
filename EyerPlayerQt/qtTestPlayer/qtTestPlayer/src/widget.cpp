#include "widget.h"
#include "./ui_widget.h"
#include "winopenglwidget.h"
#include "signalplayer.h"

#include <QPushButton>
#include <string>
#include <QFileDialog>
#include "MMPlayer/MMPlayer.h"
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    winOpenglWidget *winOpengl = new winOpenglWidget(ui->openglWidget);
    signalPlayer *s = new signalPlayer(this);
    QTimer *timer = new QTimer(this);

    ui->lineEdit->setText("c://demo/demo1.mp4");

    ui->playerTime->setDigitCount(5);
    ui->playerTime->setStyleSheet("border: 1px solid green; color: green; background: silver;");// 设置样式
    ui->playerTime->display(0);

    timer->setInterval(1000);

    connect(timer, &QTimer::timeout, this, [=](){
        ui->playerTime->display( ui->playerTime->value()+1);
        ui->horizontalSlider->setValue(ui->horizontalSlider->value()+1);
    });

    connect(ui->openPathButton, &QPushButton::clicked, s, [=](){
//    打开文件
        QString filePath = QFileDialog::getOpenFileName(this,"打开","C:\\","*.mp4");
        s->openFile(this);
    });

    connect(ui->playButton, &QPushButton::clicked, s, [=](){
        if(ui->lineEdit->text().length() >= 3){
            winOpengl->createPlayer();
        }
        if(timer != nullptr){
            timer->start();
        }
//        s->play(ui->playerTime);
    });



    connect(ui->stopButton,&QPushButton::clicked, s, [=](){
        winOpengl->stopPlayer();
        s->stop();
    });

    connect(ui->continueButton, &QPushButton::clicked, s, [=](){
        winOpengl->continuePlayer();
        s->conninuePlay();
    });

    connect(ui->closeButton,&QPushButton::clicked, s, [=](){
        winOpengl->closePlayer();
        s->close();
    });



}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event){

}
