#include "include/TcpServer.hpp"

/**
 * @brief Construct a new Tcp Server:: Tcp Server object
 *        Bind tcp server using @param port and listen for
 *        new connection        
 * 
 * @param port 
 */
TcpServer::TcpServer(quint16 port)
{
    server = new QTcpServer();
    server->listen(QHostAddress::Any, port);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

/**
 * @brief Destroy the Tcp Server:: Tcp Server object
 */
TcpServer::~TcpServer()
{
}

/**
 * @brief Close all connection to client and close server
 */
void TcpServer::close()
{
    for (QTcpSocket* socket : clients)
        socket->close();
    server->close();
}

/**
 * @brief Send message to all connected client
 * 
 * @param msg 
 */
void TcpServer::sendMessage(Message msg)
{
    for (QTcpSocket* socket : clients)
        socket->write(msg.toQByteArray());
}

/**
 * @brief function call every time a new connection happen
 */
void TcpServer::onNewConnection()
{
    QTcpSocket *client = server->nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(client, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    clients.push_back(client);
}

/**
 * @brief Detect when a client disconnect to remove it form client list
 * 
 * @param socketState 
 */
void TcpServer::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        clients.removeOne(sender);
    }
}

/**
 * @brief When server receive data, decode it here to Message object
 *        resend to every client except the send
 */
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