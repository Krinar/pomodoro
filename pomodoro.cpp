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
    QFont font_timer;
    font_timer.setPointSize(47);
    font_timer.setBold(true);
    timer->setFont(font_timer);
    timer->setText(getTime());
    timer->setStyleSheet("QLabel { padding: 20px; }");
    timer->setAlignment(Qt::AlignCenter);
    timer->setStyleSheet("color: #fff");


    // Creating the progress text
    progress = new QLabel;
    progress->setText(percentage());
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    progress->setFont(font);
    progress->setStyleSheet("color: #fff");

    // Creating the circleProgress
    CircleProgressBar = new CircularProgress(timer, 0, QColor{0,128,128}, getTime());
    timerLayout = new QHBoxLayout;
    timerLayout->addWidget(CircleProgressBar);
    timerLayout->addWidget(timer);

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

    // Creating progress layout
    progressLayout = new QHBoxLayout;
    progressLayout->addStretch();
    progressLayout->addWidget(progress);
    progressLayout->addStretch();


    /*
    // Creating stacked layout
    // Create widget for combine timer and progressBar
    QWidget *timer_widget = new QWidget();
    stacked_timer = new QVBoxLayout(timer_widget);
    // Add compenent to Layout
    //stacked_timer->addWidget(timer);
    stacked_timer->addWidget(CircleProgressBar);
    timer_circle = new QStackedLayout;
    timer_circle->setStackingMode(QStackedLayout::StackAll);
    // Add layout to StackedLayout
    timer_circle->addWidget(timer_widget);
    */


    // Creating the info layout
    infoLayout = new QVBoxLayout();
    infoLayout->addWidget(sessionType);

    // Creating main layout
    mainLayout = new QVBoxLayout;
    mainLayout->addStretch();
    mainLayout->addLayout(infoLayout);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(timerLayout);
    mainLayout->addLayout(progressLayout);
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
