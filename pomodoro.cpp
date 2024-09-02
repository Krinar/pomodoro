#include "pomodoro.h"

Pomodoro::Pomodoro(QWidget *parent) : QWidget(parent) {
    setVariables();

    createLayout();
    initializeTimer();

    connect(this, SIGNAL(sessionEnd()), this, SLOT(nextSession()));
    connect(this, SIGNAL(sessionEnd()), this, SLOT(updateSessiontype()));
    setLayout(mainLayout);
    setFixedHeight(350);
}

void Pomodoro::setVariables() {
    workSession = true;
    sessionCount = 0;
    session = 25;
    rest = 5;
    timeElapsed = 60 * session;
    stop = session * 60;
}

void Pomodoro::createLayout() {

    startButton = new QPushButton();
    connect(startButton, SIGNAL(clicked()), this, SLOT(startPomodoro()));
    startButton->setStyleSheet("border: none; color: #fff");
    QPixmap pixmap(":/icons/Resources/play.png");
    QIcon ButtonIcon(pixmap);
    startButton->setIcon(ButtonIcon);
    startButton->setIconSize(QSize(100, 100));//(pixmap.rect().size());

    stopButton = new QPushButton();
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopPomodoro()));
    stopButton->setStyleSheet("border: none; color: #fff");
    QPixmap stopPixmap(":/icons/Resources/stop.png");
    QIcon stopIcon(stopPixmap);
    stopButton->setIcon(stopIcon);
    stopButton->setIconSize(QSize(100, 100));//stopPixmap.rect().size());


    resetButton = new QPushButton();
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetPomodoro()));
    resetButton->setStyleSheet("border: none; color: #fff");
    QPixmap resetPixmap(":/icons/Resources/reset.png");
    QIcon resetIcon(resetPixmap);
    resetButton->setIcon(resetIcon);
    resetButton->setIconSize(QSize(100, 100));//(resetPixmap.rect().size());

    // Creating the timer text
    timer = new QLabel;
    timer->setText(getTime());
    QFont font;
    font.setPointSize(65);
    font.setBold(true);
    timer->setFont(font);
    timer->setStyleSheet("color: #fff");

    // Creating info to display:
    sessionType = new QLabel("WORK");
    sessionType->setAlignment(Qt::AlignCenter);
    font.setPointSize(20);
    sessionType->setFont(font);
    sessionType->setStyleSheet("color: #fff;");


    // Creating button layout
    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(stopButton);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addWidget(resetButton);

    // Creating timer layout
    timerLayout = new QHBoxLayout;
    timerLayout->addStretch();
    timerLayout->addWidget(timer);
    timerLayout->addStretch();

    // Creating the info layout
    infoLayout = new QVBoxLayout();
    infoLayout->addWidget(sessionType);

    // Creating main layout
    mainLayout = new QVBoxLayout;
    mainLayout->addStretch();
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(timerLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addSpacing(20);



}

void Pomodoro::initializeTimer() {
    counter = new QTimer;
    connect(counter, SIGNAL(timeout()), this, SLOT(secondPassed()));
}

void Pomodoro::secondPassed() {
    timeElapsed--;
    updateTimer();
}

void Pomodoro::updateTimer() {
    // Checking if the session ended
    if (timeElapsed < 0) {
        emit sessionEnd();
    }

    timer->setText(getTime());
}

void Pomodoro::startPomodoro() {
    counter->start(1000);
}

void Pomodoro::stopPomodoro() {
    counter->stop();
}

QString Pomodoro::getTime() {
    int sec = timeElapsed % 60;
    int min = timeElapsed / 60;

    QString sec_string;
    if (sec < 10) sec_string = "0" + QString::number(sec);
    else sec_string = QString::number(sec);

    QString min_string;
    if (min < 10) min_string = "0" + QString::number(min);
    else min_string = QString::number(min);

    return min_string + ":" + sec_string;
}

void Pomodoro::resetPomodoro() {
    timeElapsed = 60 * session;
    counter->stop();
    updateTimer();

    sessionCount = 0;
    workSession = true;

    emit sessionTypeChanged();
}

void Pomodoro::nextSession() {
    if (workSession) {
        workSession = false;
        timeElapsed = rest * 60;

        emit sessionTypeChanged();
    } else {
        workSession = true;
        timeElapsed = session * 60;
        sessionCount++;

        emit sessionTypeChanged();
    }
}

void Pomodoro::updateSessiontype() {
    QString text;
    if (workSession) text = "Work";
    else text = "Rest";

    sessionType->setText(text);
}

void Pomodoro::quitResponse() {
    emit quitApp();
}

void Pomodoro::showResponse() {
    emit showApp();
}
