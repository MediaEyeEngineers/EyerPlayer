#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "EyerPlayerLib.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public EyerPlayer::EyerPlayerOpenCB, public EyerPlayer::EyerPlayerStopCB
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

    virtual int onOpen(EyerPlayer::EventOpenStatus status, EyerPlayer::VideoInfo & videoInfo);
    virtual int onStop(EyerPlayer::EventStopStatus status);

public slots:
    void ClickOpen();
    void ClickStop();
private:
    Ui::MainWindow *ui;

    EyerPlayer::EyerPlayerView * player = nullptr;
};

#endif // MAINWINDOW_H
