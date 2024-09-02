#ifndef POMODORO_H
#define POMODORO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>

class Pomodoro : public QWidget
{
    Q_OBJECT

public:
    Pomodoro(QWidget *parent = nullptr);

private:
    bool workSession;
    int sessionCount;
    int timeElapsed;
    int session;
    int rest;
    int stop;

    QTimer *counter;

    // UI
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *resetButton;
    QLabel      *timer;
    QLabel      *sessionType;

    //Layouts
    QHBoxLayout *buttonsLayout;
    QHBoxLayout *timerLayout;
    QVBoxLayout *infoLayout;
    QVBoxLayout *mainLayout;



    //Methods
    void createLayout();
    void initializeTimer();
    void updateTimer();
    void setVariables();


    QString getTime();

private slots:
    void startPomodoro();
    void stopPomodoro();
    void resetPomodoro();
    void secondPassed();
    void nextSession();
    void updateSessiontype();
    void showResponse();
    void quitResponse();

signals:
    void sessionEnd();
    void sessionTypeChanged();
    void quitApp();
    void showApp();
};




#endif // POMODORO_H
