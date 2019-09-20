#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <sysinfoqml.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SysInfoQML>("SysInfoQML", 1, 0, "SysInfoQML");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
