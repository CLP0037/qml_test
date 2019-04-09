#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QSerialPortInfo>  //(*.pro) QT += serialport
#include <QQmlContext>

int main(int argc, char *argv[])
{
    /********************************************************/
    QSerialPortInfo serialPortInfo;
    QList<QSerialPortInfo> ports = serialPortInfo.availablePorts();
    QList<qint32> bauds = serialPortInfo.standardBaudRates();
    QStringList portsName;
    QStringList baudsStr;

    foreach (QSerialPortInfo port, ports) {
        portsName.append(port.portName());
    }

    foreach (qint32 baud, bauds) {
        baudsStr.append(QString::number(baud));
    }

    /********************************************************/

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //portsNameModel:可用串口模型
    //baudsModel:可选波特率模型
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("portsNameModel",QVariant::fromValue(portsName));
    context->setContextProperty("baudsModel",QVariant::fromValue(baudsStr));



    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
