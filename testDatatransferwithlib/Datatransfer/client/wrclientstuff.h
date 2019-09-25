#ifndef WRCLIENTSTUFF_H
#define WRCLIENTSTUFF_H

#include <QObject>
#include <QTcpSocket>
#include <QTime>
#include <QDebug>

class WRClientStuff : public QObject
{
    Q_OBJECT
public:
    explicit WRClientStuff(const QString hostAddress, int port, QObject *parent =  nullptr);

    QTcpSocket *tcpSocket;
    bool getStatus();
    qint64 bufSend(QByteArray sendBuf);

signals:
    void statusChanged(bool);
    void msgSend(QByteArray sendBuf);
    void msgRecv(QByteArray recvBuf);

public slots:
    void closeConnection();
    void connect2host(int timeout);

private slots:
    void readyRead();


private:
    QString mHost;
    int mPort;
    bool mStatus;

};

#endif // WRCLIENTSTUFF_H
