#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>

#include <iostream>

#include <include/TcpSocket.hpp>

class TcpClient : public TcpSocket
{
Q_OBJECT
private
:
    QTcpSocket *client;

public:
    TcpClient(quint16 port);
    ~TcpClient();

    void close();
    void sendMessage(QString text);

private slots:
    void onReadyRead();
    void onDisconnection();
};

#endif