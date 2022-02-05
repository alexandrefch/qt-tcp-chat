#ifndef CHAT_WINDOW_HPP
#define CHAT_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <iostream>

#include "include/InputWidget.hpp"
#include "include/ConversationWidget.hpp"
#include "include/TcpServer.hpp"
#include "include/TcpClient.hpp"

#define WINDOW_SIZE  400
#define WINDOW_TITLE "ChatApp"

class ChatWindow : public QWidget
{
Q_OBJECT
private:
    ConversationWidget *convWidget;
    InputWidget        *inputWidget;
    TcpSocket          *tcpSocket;

public:
    ChatWindow(bool isServer);
    ~ChatWindow();

private:
    void closeEvent(QCloseEvent *event);

private slots:
    void receiveMessage(QString text);
    void sendMessage(QString text);
};

#endif