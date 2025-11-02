#include "pomodoro.h"

Pomodoro::Pomodoro(QWidget *parent) : QWidget(parent) {

    setVariables();
    createLayout();
    initializeTimer();

    connect(this, SIGNAL(sessionEnd()), this, SLOT(nextSession()));
    connect(this, SIGNAL(sessionEnd()), this, SLOT(updateSessiontype()));
    setLayout(mainLayout);
    setFixedHeight(500);


}

void Pomodoro::setVariables() {
    workSession = true;
    sessionCount = 0;
    session = 1;
    rest = 5;
    timeElapsed = 60 * session;
    stop = session * 60;
}

void Pomodoro::createLayout() {

    startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(startPomodoro()));
    startButton->setFixedSize(120, 50);
    startButton->setStyleSheet(R"(
            QPushButton {
                font-family: 'Inconsolata Nerd Font Mono';
                border: none;
                color: #fff;
                font-size: 20px;
                padding: 15px 5px;
                background-color: #1A535C;
                border-radius: 10px;
            }
            QPushButton:hover {
                background-color: #2E2E2E;
            }
            )");

    stopButton = new QPushButton("Stop");
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopPomodoro()));
    stopButton->setFixedSize(120, 50);
    stopButton->setStyleSheet(R"(
            QPushButton {
                font-family: 'Inconsolata Nerd Font Mono';
                border: none;
                color: #fff;
                font-size: 20px;
                padding: 15px 5px;
                background-color: #1A535C;
                border-radius: 10px;
            }
            QPushButton:hover {
                background-color: #2E2E2E;
            }
            )");

    resetButton = new QPushButton("Reset");
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetPomodoro()));
    resetButton->setFixedSize(120, 50);
    resetButton->setStyleSheet(R"(
            QPushButton {
                font-family: 'Inconsolata Nerd Font Mono';
                border: none;
                color: #fff;
                font-size: 20px;
                padding: 15px 5px;
                background-color: #1A535C;
                border-radius: 10px;
            }
            QPushButton:hover {
                background-color: #2E2E2E;
            }
            )");



    // Creating the timer text

    timer = new QLabel;
    QFont font_timer;
    font_timer.setPointSize(47);
    font_timer.setBold(true);
    timer->setFont(font_timer);
    timer->setText(getTime());
    timer->setStyleSheet("QLabel { padding: 20px; }");
    timer->setAlignment(Qt::AlignCenter);
    timer->setStyleSheet("color: #1E2D3D");


    // Creating the progress text
    progress = new QLabel;
    progress->setText(percentage());
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    progress->setFont(font);
    progress->setStyleSheet("color: #1A535C");

    // Creating the circleProgress
    CircleProgressBar = new CircularProgress(progress, 0, QColor("#1A535C"), getTime());
    timerLayout = new QHBoxLayout;
    timerLayout->addWidget(CircleProgressBar);

    // Creating info to display:
    sessionType = new QLabel("WORK");
    sessionType->setAlignment(Qt::AlignCenter);
    font.setPointSize(20);
    sessionType->setFont(font);
    sessionType->setStyleSheet("color: #2E2E2E;");


    // Creating count completed
    countCompleted = new QHBoxLayout;
    countProgress = new QLabel("Completed:");
    countProgress->setAlignment(Qt::AlignCenter);
    font.setPointSize(20);
    countProgress->setFont(font);
    countProgress->setStyleSheet("color: #1A535C;");
    countCompleted->addWidget(countProgress);
    /// TODO
    // QLabel *tomato = new QLabel();
    // tomato->setPixmap(QPixmap(":/icons/Resources/tomatoes_2_32x32.png"));
    // countCompleted->addWidget(tomato);




    // Creating button layout
    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(stopButton);
    buttonsLayout->addSpacing(10);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addSpacing(10);
    buttonsLayout->addWidget(resetButton);
    buttonsLayout->addStretch();

    // Creating progress layout
    progressLayout = new QHBoxLayout;
    progressLayout->addStretch();
    progressLayout->addWidget(progress);
    progressLayout->addStretch();

    // Creating the info layout
    infoLayout = new QVBoxLayout();
    infoLayout->addWidget(sessionType);

    // Creating main layout
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(timerLayout);
    mainLayout->addLayout(progressLayout);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(countCompleted);
    mainLayout->addSpacing(20);
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
    QString timer_text = getTime();
    timer->setText(timer_text);
    progress->setText(percentage());
    CircleProgressBar->text_timer = timer_text;
    CircleProgressBar->value = (100 - timeElapsed / 60. * 100 / 25) / 100;
    CircleProgressBar->update();

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

QString Pomodoro::percentage() {
    if (workSession) return QString::number(int((100 - timeElapsed / 60. * 100 / 25))) + '%';
    else return QString::number(int((100 - timeElapsed / 60. * 100 / 5))) + '%';
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
    else text = "REST";

    sessionType->setText(text);
}

void Pomodoro::quitResponse() {
    emit quitApp();
}

void Pomodoro::showResponse() {
    emit showApp();
}
