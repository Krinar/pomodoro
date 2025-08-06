#ifndef CIRCULARPROGRESS_H
#define CIRCULARPROGRESS_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QLabel>

class CircularProgress : public QWidget {
    Q_OBJECT

public:
    CircularProgress(QWidget *parent = nullptr, double value = 0.0, QColor color = Qt::blue, QString text_timer = "")
        : QWidget(parent), value(value), color(color), text_timer(text_timer){
        setFixedSize(790, 790);
    }
public:
    double value;
    QString text_timer;
    //QFont font_timer = QFont("Inter", 50);
    QFont font_timer = QFont("Inconsolata", 60, QFont::DemiBold);

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRect rectangle((width() - 250) / 2, (height() - 750) / 2, 250, 250);
        int startAngle = 90 * 16;
        int spanAngle = -value * 360 * 16;

        painter.setPen(QPen(QColor("#4ECDC4"), 10));
        painter.drawArc(rectangle, 0, 360 * 20);

        painter.setPen(QPen(QColor("#1A535C"), 10)); //1A535C
        painter.drawArc(rectangle, startAngle, spanAngle);
        painter.setPen(QPen(QColor("2E2E2E"), 10));
        painter.setFont(font_timer);
        painter.drawText(rectangle, Qt::AlignCenter, text_timer);
    }

private:
    QColor color;
};


#endif // CIRCULARPROGRESS_H
