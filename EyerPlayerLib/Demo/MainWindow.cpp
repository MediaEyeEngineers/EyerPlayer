#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "EyerPlayerLib.h"
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new EyerPlayer::EyerPlayerView(this);
    // player->SetURL("/Users/lichi/Downloads/big_buck_bunny_1080p_surround.avi");
    // player->SetURL("/Users/lichi/Downloads/time_clock_1h_1920x1080_60fps.mp4");
    player->SetURL("/Users/lichi/Downloads/bbb_sunflower_2160p_60fps_normal.mp4");
    // player->SetURL("/Users/lichi/Downloads/1080pCaton.mkv");

    // player->SetURL("/home/redknot/Videos/bbb_sunflower_2160p_60fps_normal.mp4");


    ui->video_player_layout->addWidget(player);

    connect(ui->btn_open, SIGNAL(clicked()), this, SLOT(ClickOpen()));
    connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(ClickStop()));

    ui->video_progress_slider->setRange(0,1000);
    ui->video_progress_slider->setValue(0);
}

MainWindow::~MainWindow()
{
    if(player != nullptr){
        qDebug() << "Delete" << endl;
        delete player;
        player = nullptr;
    }
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Close" << endl;
}

void MainWindow::ClickOpen()
{
    player->Open(this);
    ui->btn_open->setEnabled(false);
}

void MainWindow::ClickStop()
{
    player->Stop(this);
}

int MainWindow::onOpen(EyerPlayer::EventOpenStatus status, EyerPlayer::VideoInfo & videoInfo)
{
    if(status == EyerPlayer::EventOpenStatus::OPEN_STATUS_SUCCESS){
        ui->log_label->setText("Open Success");

        qDebug() << "" << endl;
    }
    if(status == EyerPlayer::EventOpenStatus::OPEN_STATUS_FAIL){
        ui->log_label->setText("Open Fail");
    }
    if(status == EyerPlayer::EventOpenStatus::OPEN_STATUS_BUSY){
        ui->log_label->setText("Player is busy, Please stop first");
    }

    ui->btn_open->setEnabled(true);
    return 0;
}

int MainWindow::onStop(EyerPlayer::EventStopStatus status)
{
    if(status == EyerPlayer::EventStopStatus::STOP_STATUS_SUCCESS){
        ui->log_label->setText("Stop Success");
    }
    if(status == EyerPlayer::EventStopStatus::STOP_STATUS_FAIL){
        ui->log_label->setText("Stop Success");
    }
    if(status == EyerPlayer::EventStopStatus::STOP_STATUS_NOT_OPEN){
        ui->log_label->setText("Stop Fail, Please open first");
    }
    return 0;
}
