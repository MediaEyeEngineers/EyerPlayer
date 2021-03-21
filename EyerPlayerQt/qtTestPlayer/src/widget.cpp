#include "widget.h"
#include "./ui_widget.h"
#include "winopenglwidget.h"
#include "signalplayer.h"

#include <QPushButton>
#include <string>
#include <QFileDialog>
#include "MMPlayer/MMPlayer.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    winOpenglWidget *winOpengl = new winOpenglWidget(ui->openglWidget);
    signalPlayer *s = new signalPlayer(this);
    ui->lineEdit->setText("c://demo/demo1.mp4");

    connect(ui->openPathButton, &QPushButton::clicked, s, [=](){
//    打开文件
        QString filePath = QFileDialog::getOpenFileName(this,"打开","C:\\","*.mp4");
        s->openFile(this);
    });

    connect(ui->playButton,&QPushButton::clicked, s, [=](){
        if(ui->lineEdit->text().length() >= 3){
            winOpengl->createPlayer();
        }
        s->play(ui->playerTime);
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
