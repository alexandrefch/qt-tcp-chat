#ifndef INPUT_WIDGET_HPP
#define INPUT_WIDGET_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include "include/Message.hpp"

class InputWidget : public QWidget
{
Q_OBJECT
private:
    unsigned int size;
    QTextEdit   *inputField;
    QPushButton *sendButton;
    
public:
    InputWidget(unsigned int size);
    ~InputWidget();

signals:
    void sendMessage(Message msg);

private slots:
    void onSendMessage();
};

#endif