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
    player->SetURL("/Users/lichi/Downloads/nezha.mp4");
    player->SetURL("/Users/lichi/Downloads/solo.mp3");
    // player->SetURL("/Users/lichi/Downloads/1080pCaton.mkv");

    // player->SetURL("C:/Users/redknot/Downloads/1080pCaton.mkv");
    // player->SetURL("C:/Users/redknot/Downloads/bbb_sunflower_2160p_60fps_normal.mp4");

    player->SetProgressCB(this);

    // player->SetURL("/home/redknot/Videos/bbb_sunflower_2160p_60fps_normal.mp4");


    ui->video_player_layout->addWidget(player);

    connect(ui->btn_open, SIGNAL(clicked()), this, SLOT(ClickOpen()));
    connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(ClickStop()));
    connect(ui->btn_play, SIGNAL(clicked()), this, SLOT(ClickPlay()));
    connect(ui->btn_pause, SIGNAL(clicked()), this, SLOT(ClickPause()));

    ui->video_progress_slider->setRange(0,1000);
    ui->video_progress_slider->setValue(0);

   // ui->video_progress_slider->setTickPosition(QSlider::TicksAbove);

    connect(ui->video_progress_slider, SIGNAL(valueChanged(int)), this, SLOT(progressValueChanged(int)));
    connect(ui->video_progress_slider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(ui->video_progress_slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));
    connect(ui->video_progress_slider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));

    player->Open(this);
}

MainWindow::~MainWindow()
{
    if(player != nullptr){
        delete player;
        player = nullptr;
    }
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(player != nullptr){
        player->Stop(nullptr);
    }
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

void MainWindow::ClickPlay()
{
    player->Play();
}

void MainWindow::ClickPause()
{
    player->Pause();
}

int MainWindow::onOpen(EyerPlayer::EventOpenStatus status, EyerPlayer::MediaInfo & mediaInfo)
{
    if(status == EyerPlayer::EventOpenStatus::OPEN_STATUS_SUCCESS){
        ui->log_label->setText("Open Success");

        for(int i=0;i<mediaInfo.GetStreamCount();i++){
            EyerPlayer::StreamInfo info;
            mediaInfo.GetStream(i, info);

            ui->time_start->setText(QString::number(0.0, 'f', 2));
        }

        videoDuration = mediaInfo.duration;
        ui->time_end->setText(QString::number(videoDuration, 'f', 2));
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

int MainWindow::onProgress(double playTime)
{
    double p = playTime / videoDuration;
    ui->time_start->setText(QString::number(playTime, 'f', 2));
    if(!isMove){
        ui->video_progress_slider->setValue((int)(p * 1000));
    }

    return 0;
}

void MainWindow::progressValueChanged(int val)
{
    double p = val * 1.0 / 1000;
    double time = videoDuration * p;
}

void MainWindow::sliderPressed()
{
    isMove = 1;
}

void MainWindow::sliderMoved(int position)
{
    double p = position * 1.0 / 1000;
    double time = videoDuration * p;
}

void MainWindow::sliderReleased()
{
    int position = ui->video_progress_slider->value();
    double p = position * 1.0 / 1000;
    double time = videoDuration * p;

    //  qDebug() << time << endl;

    player->Seek(time);

    isMove = 0;
}
