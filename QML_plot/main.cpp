#include <QtPrintSupport/QPrinter>
//#include <QGuiApplication>
#include<QApplication>
#include <QQmlApplicationEngine>

#include "qmlplot.h"
#include <QDebug>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QGuiApplication app(argc, argv);

    qDebug()<<"qApp->applicationDirPath():"<< qApp->applicationDirPath();




    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return a.exec();
}
