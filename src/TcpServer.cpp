#include "include/TcpServer.hpp"

TcpServer::TcpServer(quint16 port)
{
    server = new QTcpServer();
    server->listen(QHostAddress::Any, port);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

TcpServer::~TcpServer()
{
}

void TcpServer::close()
{
    for (QTcpSocket* socket : clients)
        socket->close();
    server->close();
}

void TcpServer::sendMessage(Message msg)
{
    for (QTcpSocket* socket : clients)
        socket->write(msg.toQByteArray());
}

void TcpServer::onNewConnection()
{
    QTcpSocket *client = server->nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(client, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    clients.push_back(client);
}

void TcpServer::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        clients.removeOne(sender);
    }
}

void TcpServer::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    emit onReceiveMessage(datas);
    
    for (QTcpSocket* socket : clients) {
        if (socket != sender)
            socket->write(datas);
    }
}