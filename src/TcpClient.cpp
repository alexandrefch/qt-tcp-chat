#include "include/TcpClient.hpp"

/**
 * @brief Construct a new Tcp Client:: Tcp Client object
 *        Conenct a tcp scoket to localhost using @param port
 * 
 * @param port 
 */
TcpClient::TcpClient(quint16 port)
{
    client = new QTcpSocket();
    client->connectToHost(QHostAddress("127.0.0.1"), port);
    connect(client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnection()));
}

/**
 * @brief Destroy the Tcp Client:: Tcp Client object
 */
TcpClient::~TcpClient()
{
}

/**
 * @brief Disconnect the client
 */
void TcpClient::close()
{
    client->close();
}

/**
 * @brief Send message to the server
 * 
 * @param msg 
 */
void TcpClient::sendMessage(Message msg)
{
    client->write(msg.toQByteArray());
}

/**
 * @brief Function call everytime tcpClient receive data
 */
void TcpClient::onReadyRead()
{
    emit onReceiveMessage(Message(client->readAll()));
}

/**
 * @brief When the client is disconnected from the server
 *        write a message in the chat to notice the user
 */
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