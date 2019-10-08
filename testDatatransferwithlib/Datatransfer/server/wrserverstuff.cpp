#include "wrserverstuff.h"

WRServerStuff::WRServerStuff(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);

}

QList<QTcpSocket *> WRServerStuff::getClients()
{
    return clients;
}

int WRServerStuff::startListen(int port)
{
    clients.clear();
    clients_ip.clear();
    clients_port.clear();
    if(!tcpServer->listen(QHostAddress::Any, port))
    {
        return -1;
    }
    connect(this->tcpServer, &QTcpServer::newConnection, this, &WRServerStuff::newConnection);
    return 0;
}

void WRServerStuff::stopListen()
{
    if(tcpServer->isListening())
    {
        disconnect(tcpServer, &QTcpServer::newConnection, this, &WRServerStuff::newConnection);

        QList<QTcpSocket *> clients = this->getClients();
        for(int i = 0; i < clients.count(); i++)
        {

            switch (clients.at(i)->state())
            {
                case 0:
                    clients.at(i)->disconnectFromHost();

                    break;
                case 2:
                    clients.at(i)->abort();

                    break;
                default:
                    clients.at(i)->abort();
            }
        }

        tcpServer->close();
        //post is closed
    }
}

qint64 WRServerStuff::sendbufToClient(int index, QByteArray sendBuf)
{
    if(this->getClients().count()>index)
    {
        QTcpSocket *clientSocket = clients.at(index);
        return clientSocket->write(sendBuf,sendBuf.size());
    }
    else
    {
        return -1;
    }
}
void WRServerStuff::newConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &WRServerStuff::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &WRServerStuff::gotDisconnection);

    clients << clientSocket;

//    qDebug()<<"clientSocket->peerAddress():"<<clientSocket->peerAddress().toString();
//    //qDebug()<<"clientSocket->peerName():"<<clientSocket->peerName();//""?
//    qDebug()<<"clientSocket->peerPort():"<<clientSocket->peerPort();

    QString ip="";int port=0;
    int index = clients.indexOf(clientSocket);//(QTcpSocket*)sender()
    QString temp_ip = clients.at(index)->peerAddress().toString();
    int pos = temp_ip.lastIndexOf(":");
    ip = temp_ip.mid(pos+1);
    port = clients.at(index)->peerPort();

    clients_ip.append(ip);
    clients_port.append(port);
    emit(clientNewConnect(ip,port));

}

void WRServerStuff::readClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();

    qDebug()<<"tcpSocket->bytesAvailable():"<<clientSocket->bytesAvailable();
    int index = clients.indexOf(clientSocket);//(QTcpSocket*)sender()
    QString ip="";int port=0;
    ip = clients_ip.at(index);
    port = clients_port.at(index);

    if(clientSocket->bytesAvailable() <= 0)
    {
        //clients.removeOne(clientSocket);

        clients.removeAt(index);
        clients_ip.removeAt(index);
        clients_port.removeAt(index);
        emit clientDisconnected(ip,port);
        return;
    }


    QByteArray readBuf = clientSocket->readAll();
//    QString str;
//    for(int i=0;i<readBuf.size();i++)
//    {
//        str += QString("%1").arg(readBuf[i],2,16,QLatin1Char('0'));
//        str += " ";
//    }
//    qDebug()<<"msgRecv:"<<str<<"(size="<<readBuf.size()<<")";
//    //emit gotNewMesssage(str);
    emit(msgRecv(ip,port,readBuf));
}

void WRServerStuff::gotDisconnection()
{

    //clients.removeAt(clients.indexOf((QTcpSocket*)sender()));
    int index = clients.indexOf((QTcpSocket*)sender());

    QString ip="";int port=0;

//    QString temp_ip = clients.at(index)->peerAddress().toString();
//    int pos = temp_ip.lastIndexOf(":");
//    ip = temp_ip.mid(pos+1);
//    port = clients.at(index)->peerPort();
    ip = clients_ip.at(index);
    port = clients_port.at(index);
    clients.removeAt(index);
    clients_ip.removeAt(index);
    clients_port.removeAt(index);
    emit clientDisconnected(ip,port);
}

qint64 WRServerStuff::sendToClient(QTcpSocket *socket, QByteArray sendBuf)
{
    //
    return socket->write(sendBuf,sendBuf.size());
}

