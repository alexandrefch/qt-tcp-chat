#include "include/ConversationWidget.hpp"

/**
 * @brief Construct a new Conversation Widget:: Conversation Widget object
 *        Create a scrollarea tu make endless and create the vertical layout
 *        to handle message
 */
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

/**
 * @brief Destroy the Conversation Widget:: Conversation Widget object
 */
ConversationWidget::~ConversationWidget()
{
}

/**
 * @brief Display message inside the vertical layout
 * 
 * @param msg 
 */
void ConversationWidget::displayMessage(Message msg)
{
    this->messageLayout->addWidget(msg.toQLabel());
}