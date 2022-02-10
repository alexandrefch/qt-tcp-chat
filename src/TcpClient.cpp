#include "include/TcpClient.hpp"

TcpClient::TcpClient(quint16 port)
{
    client = new QTcpSocket();
    client->connectToHost(QHostAddress("127.0.0.1"), port);
    connect(client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnection()));
}

TcpClient::~TcpClient()
{
}

void TcpClient::close()
{
    client->close();
}

void TcpClient::sendMessage(Message msg)
{
    client->write(msg.toQByteArray());
}

void TcpClient::onReadyRead()
{
    emit onReceiveMessage(Message(client->readAll()));
}

void TcpClient::onDisconnection()
{
    emit onReceiveMessage(
        Message(
            "Déconnexion du serveur distant !",
            false,
            MessageType::PROGRAM
            )
        );
}