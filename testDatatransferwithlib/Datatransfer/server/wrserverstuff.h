#ifndef WRSERVERSTUFF_H
#define WRSERVERSTUFF_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class WRServerStuff : public QObject
{
    Q_OBJECT
public:
    explicit WRServerStuff(QObject *parent = nullptr);
    QTcpServer *tcpServer;
    QList<QTcpSocket *> getClients();
    int startListen(int port);
    void stopListen();
    qint64 sendbufToClient(int index, QByteArray sendBuf);

signals:
    void clientNewConnect(QString ip , int port);
    void clientDisconnected(QString ip , int port);
    //void msgSend(QByteArray sendBuf);
    void msgRecv(QString ip , int port,QByteArray recvBuf);

public slots:

    virtual void newConnection();//
    void readClient();
    void gotDisconnection();
    qint64 sendToClient(QTcpSocket *socket, QByteArray sendBuf);

private:
    QList<QTcpSocket*> clients;
    QStringList clients_ip;
    QList<int> clients_port;
};

#endif // WRSERVERSTUFF_H
