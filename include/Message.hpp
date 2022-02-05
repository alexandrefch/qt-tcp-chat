#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>

enum MessageType { SEND, RECEIVE };

class Message : public QWidget
{
Q_OBJECT
public:
    Message(QString content, MessageType type);
    ~Message();
};

#endif