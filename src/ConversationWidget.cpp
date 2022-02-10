#include "include/ConversationWidget.hpp"

ConversationWidget::ConversationWidget()
{
    this->messageLayout = new QVBoxLayout;
    this->messageLayout->setAlignment(Qt::AlignTop);
    this->messageLayout->setSpacing(0);
    this->messageLayout->setMargin(0);
    QWidget *content = new QWidget;
    content->setLayout(messageLayout);
    
    setWidgetResizable(true);
    setWidget(content);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

ConversationWidget::~ConversationWidget()
{
}


void ConversationWidget::displayMessage(Message msg)
{
    this->messageLayout->addWidget(msg.toQLabel());
}