#ifndef CIRCULARPROGRESS_H
#define CIRCULARPROGRESS_H

#include <QApplication>
#include <QWidget>
#include <QPainter>

class CircularProgress : public QWidget {
    Q_OBJECT

public:
    CircularProgress(QWidget *parent = nullptr, double value = 0.0, QColor color = Qt::blue)
        : QWidget(parent), value(value), color(color) {
        setFixedSize(100, 100);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRectF rectangle(10, 10, 80, 80);
        int startAngle = 90 * 16;
        int spanAngle = -value * 360 * 16;

        painter.setPen(QPen(Qt::gray, 10));
        painter.drawArc(rectangle, 0, 360 * 16);

        painter.setPen(QPen(color, 10));
        painter.drawArc(rectangle, startAngle, spanAngle);

        painter.setPen(Qt::black);
        painter.drawText(rectangle, Qt::AlignCenter, QString::number(value * 100) + "%");
    }

private:
    double value;
    QColor color;
};

/*
    QHBoxLayout *layout = new QHBoxLayout(&window);

    layout->addWidget(new CircularProgress(&window, 0.1, Qt::cyan));
    layout->addWidget(new CircularProgress(&window, 0.33, Qt::magenta));
    layout->addWidget(new CircularProgress(&window, 0.5, Qt::green));
    layout->addWidget(new CircularProgress(&window, 0.75, Qt::red));
    layout->addWidget(new CircularProgress(&window, 1.0, QColor{0,128,128}));

    window.setLayout(layout);
    window.show();
    return a.exec();

*/


#endif // CIRCULARPROGRESS_H
