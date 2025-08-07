#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    pomodoro = new Pomodoro;
    this->setCentralWidget(pomodoro);


    // WINDOW
    //this->setWindowFlags(Qt::CustomizeWindowHint);
    setStyleSheet("background-color: #F4F4F9");
    setWindowTitle("Pomodoro");
    setFixedHeight(500);
    setFixedWidth(800);
    QIcon WindowIcon(":/icons/Resources/tomatoes_2.png");
    this->setWindowIcon(WindowIcon);

    connect(pomodoro, SIGNAL(quiteApp()), this, SLOT(close()));
    connect(pomodoro, SIGNAL(showApp()), this, SLOT(showNormal()));
}
