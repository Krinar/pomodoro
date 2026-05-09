#ifndef POMODORO_H
#define POMODORO_H

#include <QQuickPaintedItem>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <Settings.h>


class Pomodoro : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QColor backgroundColor MEMBER m_backgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor borderActiveColor MEMBER m_borderActiveColor NOTIFY borderActiveColorChanged)
    Q_PROPERTY(QColor borderNonActiveColor MEMBER m_borderNonActiveColor NOTIFY borderNonActiveColorChanged)
    Q_PROPERTY(qreal angle MEMBER m_angle NOTIFY angleChanged)
    Q_PROPERTY(QTime circleTime MEMBER m_circleTime NOTIFY circleTimeChanged)

public:
    explicit Pomodoro(QQuickItem *parent = 0);

    void paint(QPainter *painter) override;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    QString name() const;
    QColor backgroundColor() const;
    QColor borderActiveColor() const;
    QColor borderNonActiveColor() const;
    qreal angle() const;
    QTime circleTime() const;



public slots:
    void setName(const QString name);
    void setBackgroundColor(const QColor backgroundColor);
    void setBorderActiveColor(const QColor borderActiveColor);
    void setBorderNonActiveColor(const QColor borderNonActiveColor);
    void setAngle(const qreal angle);
    void setCircleTime(const QTime circleTime);


signals:

    void cleared();
    void nameChanged(const QString name);
    void backgroundColorChanged(const QColor backgroundColor);
    void borderActiveColorChanged(const QColor borderActiveColor);
    void borderNonActiveColorChanged(const QColor borderNonActiveColor);
    void angleChanged(const qreal angle);
    void circleTimeChanged(const QTime circleTime);

private:
    QString     m_name;                 // Название объекта, по большей части до кучи добавлено
    QColor      m_backgroundColor;      // Основной цвет фона
    QColor      m_borderActiveColor;    // Цвет ободка, заполняющий при прогрессе ободок таймера
    QColor      m_borderNonActiveColor; // Цвет ободка фоновый
    qreal       m_angle;                // Угол поворота графика типа пирог, будет формировать прогресс на ободке
    QTime       m_circleTime;           // Текущее время таймера
    QTimer      *internalTimer;         // Таймер, по которому будет изменяться время

    PomodoroTimeSettings settings;
};

#endif // POMODORO_H
