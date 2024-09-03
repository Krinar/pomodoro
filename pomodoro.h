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

    struct defaultPomodoroSetting {
        const int WORK = 25;
        const int REST = 5;
    };

    QTimer *counter;

    // UI
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *resetButton;
    QLabel      *timer;
    QLabel      *sessionType;
    QLabel      *progress;

    //Layouts
    QHBoxLayout *buttonsLayout;
    QHBoxLayout *timerLayout;
    QHBoxLayout *progressLayout;
    QVBoxLayout *infoLayout;
    QVBoxLayout *mainLayout;



    //Methods
    void createLayout();
    void initializeTimer();
    void updateTimer();
    void setVariables();


    QString getTime();
    QString percentage();

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
