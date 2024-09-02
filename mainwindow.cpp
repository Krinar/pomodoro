#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    pomodoro = new Pomodoro;
    this->setCentralWidget(pomodoro);


    // WINDOW
    //this->setWindowFlags(Qt::CustomizeWindowHint);
    setStyleSheet("background-color: #f08080");
    setWindowTitle("Pomodoro");
    //setFixedHeight(500);
    //setFixedWidth(500);

    connect(pomodoro, SIGNAL(quiteApp()), this, SLOT(close()));
    connect(pomodoro, SIGNAL(showApp()), this, SLOT(showNormal()));
}
