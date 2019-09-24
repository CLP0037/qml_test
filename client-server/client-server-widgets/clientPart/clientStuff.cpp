#include "clientStuff.h"

#include <QTime>
#include <QDebug>

ClientStuff::ClientStuff(
        const QString hostAddress,
        int portNumber,
        QObject *parent
        ) : QObject(parent), m_nNextBlockSize(0)
{
    status = false;

    host = hostAddress;
    port = portNumber;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientStuff::closeConnection);

//    timeoutTimer = new QTimer();
//    timeoutTimer->setSingleShot(true);
//    connect(timeoutTimer, &QTimer::timeout, this, &ClientStuff::connectionTimeout);
}

void ClientStuff::connect2host(int timeout)
{
    tcpSocket->connectToHost(host, port);
    QTime tm;
    tm.start();
    if(!tcpSocket->waitForConnected(timeout))//10000
    {
        qDebug()<<"connect link use time:"<<tm.elapsed();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
        return;// false
    }
    status = true;
    emit statusChanged(status);

//    timeoutTimer->start(10000);//3000
//    tcpSocket->connectToHost(host, port);
//    connect(tcpSocket, &QTcpSocket::connected, this, &ClientStuff::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientStuff::readyRead);
}

//void ClientStuff::connectionTimeout()
//{
//    //qDebug() << tcpSocket->state();
//    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
//    {
//        tcpSocket->abort();
//        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
//    }
//}

//void ClientStuff::connected()
//{
//    status = true;
//    emit statusChanged(status);
//}

bool ClientStuff::getStatus() {return status;}

void ClientStuff::readyRead()
{
    qDebug()<<"tcpSocket->bytesAvailable():"<<tcpSocket->bytesAvailable();
    QByteArray readBuf = tcpSocket->readAll();
    QString str;
    for(int i=0;i<readBuf.size();i++)
    {
        str += QString("%1").arg(readBuf[i],2,16,QLatin1Char('0'));
        str += " ";
    }
    emit hasReadSome(str);//报文信号

    //报文分析
    //分帧连帧



//    QDataStream in(tcpSocket);
//    //in.setVersion(QDataStream::Qt_5_10);
//    for (;;)
//    {
//        if (!m_nNextBlockSize)
//        {
//            if (tcpSocket->bytesAvailable() < sizeof(quint16)) { break; }
//            in >> m_nNextBlockSize;
//        }

//        if (tcpSocket->bytesAvailable() < m_nNextBlockSize) { break; }

//        QString str; in >> str;

//        if (str == "0")
//        {
//            str = "Connection closed";
//            closeConnection();
//        }

//        emit hasReadSome(str);
//        m_nNextBlockSize = 0;
//    }
}

//void ClientStuff::gotDisconnection()
//{
//    status = false;
//    emit statusChanged(status);
//}

void ClientStuff::closeConnection()
{
    //timeoutTimer->stop();

    //qDebug() << tcpSocket->state();
    disconnect(tcpSocket, &QTcpSocket::connected, 0, 0);
    disconnect(tcpSocket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}
