#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "EyerPlayerWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle("EyerPlayer");
    ui->setupUi(this);

    EyerPlayerWidget * eyerPlayer = new EyerPlayerWidget(this);
    ui->player_layout->addWidget(eyerPlayer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

