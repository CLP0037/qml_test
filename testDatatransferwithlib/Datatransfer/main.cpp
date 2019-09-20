#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "./datatransfer/devdatatransfer_wr.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    qmlRegisterType<DevDataTransfer_wr>("DevDataTransfer_wr", 1, 0, "DevDataTransfer_wr");




    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
