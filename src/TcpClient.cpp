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

void TcpClient::sendMessage(QString text)
{
    client->write(QByteArray(text.toUtf8()));
}

void TcpClient::onReadyRead()
{
    QByteArray datas = client->readAll();
    emit onReceiveMessage(datas);
}

void TcpClient::onDisconnection()
{
    emit onReceiveMessage("Déconnexion du serveur distant !\n");
}