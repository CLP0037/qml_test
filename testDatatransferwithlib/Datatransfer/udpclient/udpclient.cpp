#include "udpclient.h"

#include <QDebug>

UDPClient::UDPClient(QObject *parent) : QObject(parent)
{
    udpSendSocket = new QUdpSocket(this);

    connect(udpSendSocket,SIGNAL(readyRead()),this,SLOT(readUdpSocket()));
    //"Ready to read..."
    connect(udpSendSocket,&QUdpSocket::disconnected,[this] {qDebug()<<"udp disconnect(udpSendSocket) !";} );
}

qint64 UDPClient::bufSend_Broadcast(QByteArray sendBuf,unsigned short port)
{
    qint64 rtn = udpSendSocket->writeDatagram(sendBuf.data(),QHostAddress::Broadcast,port);
    if(rtn!=-1)
    {
        qDebug()<<"UDP单播发送成功";

    }
    else
    {
        qDebug()<<"UDP单播失败:"<<udpSendSocket->errorString();

    }
    return rtn;
}

qint64 UDPClient::bufSend_Unicast(QByteArray sendBuf,QString ip,unsigned short port)
{
    qint64 rtn = udpSendSocket->writeDatagram(sendBuf.data(),QHostAddress(ip),port);
    if(rtn!=-1)
    {
        qDebug()<<"UDP单播发送成功";
    }
    else
    {
        qDebug()<<"UDP单播失败:"<<udpSendSocket->errorString();

    }
    return rtn;
}

void UDPClient::readUdpSocket()
{
    while(udpSendSocket->hasPendingDatagrams())
    {
        QByteArray ba;
        ba.resize(udpSendSocket->pendingDatagramSize());
        udpSendSocket->readDatagram(ba.data(),ba.size());
        emit(msgRecv(ba));
    }
}
