#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //this->setWindowFlags(Qt::CustomizeWindowHint);
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
