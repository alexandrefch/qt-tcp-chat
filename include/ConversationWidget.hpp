#ifndef CONVERSATION_WIDGET_HPP
#define CONVERSATION_WIDGET_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

#include "include/Message.hpp"

class ConversationWidget : public QScrollArea
{
Q_OBJECT
private:
    QVBoxLayout *messageLayout;
    
public:
    ConversationWidget();
    ~ConversationWidget();

    void displayMessage(Message msg);
};

#endif