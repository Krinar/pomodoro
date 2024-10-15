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
        //setFixedSize(400, 400);
    }
public:
    double value;
    QString text_timer;

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRectF rectangle((width() - 70) / 2, (height() - 70) / 2, 70, 70);
        int startAngle = 90 * 16;
        int spanAngle = -value * 360 * 16;

        painter.setPen(QPen(Qt::white, 10));
        painter.drawArc(rectangle, 0, 360 * 16);

        painter.setPen(QPen(color, 10));
        painter.drawArc(rectangle, startAngle, spanAngle);
        painter.drawText(rectangle, Qt::AlignCenter, text_timer);

    }

private:
    QColor color;
};


#endif // CIRCULARPROGRESS_H
