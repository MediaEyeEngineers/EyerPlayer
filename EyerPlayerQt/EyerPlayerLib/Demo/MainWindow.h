#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "EyerPlayerLib.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public EyerPlayer::EyerPlayerOpenCB, public EyerPlayer::EyerPlayerStopCB, public EyerPlayer::EyerPlayerProgressCB, public EyerPlayer::EyerPlayerLagCB
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

    virtual int onOpen(EyerPlayer::EventOpenStatus status, EyerPlayer::MediaInfo & videoInfo);
    virtual int onStop(EyerPlayer::EventStopStatus status);

    virtual int onProgress(double playTime);

    virtual int onLagStart(long long id);
    virtual int onLagStop(long long id);

public slots:
    void ClickOpen();
    void ClickStop();

    void ClickPlay();
    void ClickPause();

    void progressValueChanged(int val);


    void sliderPressed();
    void sliderMoved(int position);
    void sliderReleased();
private:
    Ui::MainWindow *ui;
    EyerPlayer::EyerPlayerView * player = nullptr;

    double videoDuration = 0.0f;

    int isMove = 0;
};

#endif // MAINWINDOW_H
