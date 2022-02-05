#include "include/Message.hpp"

Message::Message(QString content, MessageType type)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    
    if(type == MessageType::SEND)
        layout->setAlignment(Qt::AlignRight);

    QLabel *label = new QLabel(content);
    layout->addWidget(label); 
}

Message::~Message()
{
}