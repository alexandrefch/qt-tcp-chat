#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include <QObject>

class TcpSocket : public QObject
{
Q_OBJECT
private:

public:
    TcpSocket();
    ~TcpSocket();

    virtual void sendMessage(QString text) = 0;
    virtual void close() = 0;

signals:
    void onReceiveMessage(QString text);
};

#endif