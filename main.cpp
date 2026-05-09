#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <pomodoro.h>

int main(int argc, char *argv[])
{
    // Full custom UI
    QQuickStyle::setStyle("Basic");
    qmlRegisterType<Pomodoro>("Pomodoro", 1, 0, "Pomodoro");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("pomodoro_qml", "Main");


    return app.exec();
}
