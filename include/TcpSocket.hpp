#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include <QObject>
#include "include/Message.hpp"

class TcpSocket : public QObject
{
Q_OBJECT
private:

public:
    TcpSocket();
    ~TcpSocket();

    virtual void sendMessage(Message msg) = 0;
    virtual void close() = 0;

signals:
    void onReceiveMessage(Message msg);
};

#endif