#include "wrclientstuff.h"

WRClientStuff::WRClientStuff(const QString hostAddress,
                             int port,
                             QObject *parent
                             ) : QObject(parent)
{
    mStatus = false;
    mHost = hostAddress;
    mPort = port;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &WRClientStuff::closeConnection);

}

bool WRClientStuff::getStatus()
{
    return mStatus;
}

qint64 WRClientStuff::bufSend(QByteArray sendBuf)
{
    emit(msgSend(sendBuf));
    return tcpSocket->write(sendBuf,sendBuf.size());
}




void WRClientStuff::closeConnection()
{

    disconnect(tcpSocket, &QTcpSocket::connected, nullptr, nullptr);
    disconnect(tcpSocket, &QTcpSocket::readyRead, nullptr, nullptr);

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
        mStatus = false;
        emit statusChanged(mStatus);
    }
}

void WRClientStuff::connect2host(int timeout)
{
    tcpSocket->connectToHost(mHost, mPort);
    QTime tm;
    tm.start();
    if(!tcpSocket->waitForConnected(timeout))//10000
    {
        qDebug()<<"connect link use time:"<<tm.elapsed();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
        return;// false
    }
    mStatus = true;
    emit statusChanged(mStatus);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &WRClientStuff::readyRead);
}

void WRClientStuff::readyRead()
{
    qDebug()<<"tcpSocket->bytesAvailable():"<<tcpSocket->bytesAvailable();
    QByteArray readBuf = tcpSocket->readAll();
    QString str;
    for(int i=0;i<readBuf.size();i++)
    {
        str += QString("%1").arg(readBuf[i],2,16,QLatin1Char('0'));
        str += " ";
    }
    qDebug()<<"msgRecv:"<<str<<"(size="<<readBuf.size()<<")";

    emit(msgRecv(readBuf));
}
