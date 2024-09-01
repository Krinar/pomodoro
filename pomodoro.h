#ifndef POMODORO_H
#define POMODORO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Pomodoro : public QWidget
{
    Q_OBJECT
public:
    Pomodoro(QWidget *parent = nullptr);
    void start_timer();


    QLabel *timer_display;
    QPushButton *start_timer_button;



private:
    int session;
    int rest;
};




#endif // POMODORO_H
