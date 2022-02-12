#include "include/InputWidget.hpp"

/**
 * @brief Construct a new Input Widget:: Input Widget object
 *        create button and inputfield
 * 
 * @param size height of the component
 */
InputWidget::InputWidget(unsigned int size)
{
    this->size = size;
    this->inputField = new QTextEdit();
    this->sendButton = new QPushButton("Envoyer");

    this->inputField->setFixedHeight(size);
    this->sendButton->setFixedHeight(size);

    this->inputField->setPlaceholderText("Votre message ...");

    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->addWidget(this->inputField,80);
    horizontalLayout->addWidget(this->sendButton,20);

    connect(this->sendButton, SIGNAL(clicked()), this, SLOT(onSendMessage()));
}

/**
 * @brief Destroy the Input Widget:: Input Widget object
 */
InputWidget::~InputWidget()
{
}

/**
 * @brief On clic on send button call onSendMessage
 *        clear the inputfield and emit sendMessage 
 */
void InputWidget::onSendMessage()
{
    QString text = this->inputField->toPlainText();
    this->inputField->setPlainText("");
    
    if(text.length()>0)
        emit sendMessage(Message(text,true,MessageType::USER));
}