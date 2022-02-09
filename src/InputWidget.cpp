#include "include/InputWidget.hpp"

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

InputWidget::~InputWidget()
{
}

void InputWidget::onSendMessage()
{
    QString text = this->inputField->toPlainText();
    this->inputField->setPlainText("");
    
    if(text.length()>0)
        emit sendMessage(text);
}