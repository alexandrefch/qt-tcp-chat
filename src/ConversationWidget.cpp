#include "include/ConversationWidget.hpp"

ConversationWidget::ConversationWidget()
{
    this->messageLayout = new QVBoxLayout;
    this->messageLayout->setAlignment(Qt::AlignTop);
    QWidget *content = new QWidget;
    content->setLayout(messageLayout);
    
    setWidgetResizable(true);
    setWidget(content);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

ConversationWidget::~ConversationWidget()
{
}


void ConversationWidget::displayMessage(Message *message)
{
    this->messageLayout->addWidget(message);
}