//#include <QGuiApplication>
#include<QApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "sqldb.h"
#include "model_comtradehistory.h"
#include "model_channelinfo.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SqlDB database;
    //C:/Users/Administrator/Desktop/db_wave_recorder.db
    bool rtn = database.connectToDataBase("C:/Users/Administrator/Desktop");

    if(!rtn)
    {
        qDebug()<<"connect To DataBase return false!!!";
    }
    qDebug()<<"connect To DataBase success!!!";

    Model_comtradehistory *modelComtradeHistory = new Model_comtradehistory();
    Model_ChannelInfo *modelChannelInfo = new Model_ChannelInfo();

    engine.rootContext()->setContextProperty("modelComtradefile", modelComtradeHistory);
    engine.rootContext()->setContextProperty("modelChannelinfo", modelChannelInfo);

    engine.rootContext()->setContextProperty("database", &database);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
