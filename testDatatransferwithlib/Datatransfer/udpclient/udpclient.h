#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class UDPClient : public QObject
{
    Q_OBJECT
public:
    explicit UDPClient(QObject *parent = nullptr);

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
    QUdpSocket* udpSendSocket;//client
};

#endif // UDPCLIENT_H
