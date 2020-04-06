#include "MainWindow.h"
#include <QApplication>
#include "EyerPlayerLib.h"

#include <QAudioFormat>
#include <QAudioOutput>
#include <QThread>

#include <QDebug>

#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EyerPlayer::EyerPlayerView::Init();

    MainWindow w;
    w.show();

    return a.exec();
}
