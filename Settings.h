#ifndef SETTINGS_H
#define SETTINGS_H
#include <QTime>


struct PomodoroTimeSettings {
    /*
     *
     *  Main Settings for Pomodoro session
     *
     */

    int h;  // hours
    int m;  // minutes
    int s;  // seconds
    int ms; // milliseconds

    void Clear() {
        h = 0;
        m = 0;
        s = 0;
        ms = 0;
    }

    void setDefault() {
        h = 0;
        m = 25;
        s = 0;
        ms = 0;
    }

    QTime toQTime() const {
        return QTime(h, m, s, ms);
    }
};


#endif // SETTINGS_H
