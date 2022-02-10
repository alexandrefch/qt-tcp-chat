#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>

enum MessageType { USER, PROGRAM };

class Message
{
private:
    QString     content;
    MessageType type;
    bool        isSend;

public:
    Message(QString content, bool isSend, MessageType type);
    Message(QByteArray datas);
    ~Message();

    QString getContent();
    MessageType getType();
    QByteArray toQByteArray();
    QWidget *toQLabel();
};

#endif