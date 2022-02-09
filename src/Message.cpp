#include "include/Message.hpp"

Message::Message(QString content, MessageType type)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(2);
    QLabel *label = new QLabel(content);

    if(type == MessageType::SEND)
    {
        layout->setAlignment(Qt::AlignRight);
        label->setStyleSheet(
            "background-color: #1a8fff;"
            "border-width: 0;"
            "border-radius: 8px;"
            "font: light 14px;"
            "padding: 6px;"
            "color: #FFF;"
        );
    }
    else
    {
        layout->setAlignment(Qt::AlignLeft);
        label->setStyleSheet(
            "background-color: #d9d9d9;"
            "border-width: 0;"
            "border-radius: 8px;"
            "font: light 14px;"
            "padding: 6px;"
            "color: #000;"
        );
    }
    
    layout->addWidget(label);
}

Message::~Message()
{
}