#include "udpserver.h"

#include <QDebug>

UDPServer::UDPServer(QObject *parent) : QObject(parent)
{
    udpRecSocket = new QUdpSocket(this);
}

void UDPServer::startListen(unsigned short port)
{
    udpRecSocket->bind(port,QUdpSocket::ShareAddress);

    connect(udpRecSocket,SIGNAL(readyRead()),this,SLOT(readUdpSocket()));
    //"Ready to read..."
    connect(udpRecSocket,&QUdpSocket::disconnected,[this] {qDebug()<<"udp disconnect !";} );
}

qint64 UDPServer::bufSend_Broadcast(QByteArray sendBuf,unsigned short port)
{
    qint64 rtn = udpRecSocket->writeDatagram(sendBuf.data(),QHostAddress::Broadcast,port);
    if(rtn!=-1)
    {
        qDebug()<<"UDP单播发送成功";

    }
    else
    {
        qDebug()<<"UDP单播失败:"<<udpRecSocket->errorString();

    }
    return rtn;
}

qint64 UDPServer::bufSend_Unicast(QByteArray sendBuf,QString ip,unsigned short port)
{
    qint64 rtn = udpRecSocket->writeDatagram(sendBuf.data(),QHostAddress(ip),port);
    if(rtn!=-1)
    {
        qDebug()<<"UDP单播发送成功";
    }
    else
    {
        qDebug()<<"UDP单播失败:"<<udpRecSocket->errorString();

    }
    return rtn;
}

void UDPServer::readUdpSocket()
{
    while(udpRecSocket->hasPendingDatagrams())
    {
        QByteArray ba;
        ba.resize(udpRecSocket->pendingDatagramSize());
        udpRecSocket->readDatagram(ba.data(),ba.size());
        emit(msgRecv(ba));
    }
}
