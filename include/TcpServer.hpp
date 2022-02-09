#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QAbstractSocket>

#include <include/TcpSocket.hpp>

class TcpServer : public TcpSocket
{
Q_OBJECT
private
:
    QTcpServer         *server;
    QList<QTcpSocket*>  clients;

public:
    TcpServer(quint16 port);
    ~TcpServer();

    void close();
    void sendMessage(QString text);

private slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();
};

#endif