#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class UDPServer : public QObject
{
    Q_OBJECT
public:
    explicit UDPServer(QObject *parent = nullptr);

    void startListen(unsigned short port);
    //广播发送
    qint64 bufSend_Broadcast(QByteArray sendBuf,unsigned short port);
    //单播发送
    qint64 bufSend_Unicast(QByteArray sendBuf,QString ip,unsigned short port);

signals:
    void msgSend(QByteArray sendBuf);
    void msgRecv(QByteArray recvBuf);

public slots:
    void readUdpSocket();

private:
    QUdpSocket* udpRecSocket;//server
};

#endif // UDPSERVER_H
