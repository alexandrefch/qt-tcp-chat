#include "include/Message.hpp"

Message::Message(QString content, bool isSend, MessageType type)
{
    this->content = content;
    this->type    = type;
    this->isSend  = isSend;
}

Message::Message(QByteArray datas)
{
    QString encoded = QString(datas);

    this->type    = (encoded.at(0)=='u')?MessageType::USER:MessageType::PROGRAM;
    this->isSend  = false;
    this->content = encoded.remove(0,1);

}

Message::~Message()
{

}

QString Message::getContent()
{
    return content;
}

MessageType Message::getType()
{
    return type;
}

QByteArray Message::toQByteArray()
{
    QString encoded = (type==MessageType::USER?'u':'p') + content;
    return QByteArray(encoded.toUtf8());
}

QWidget *Message::toQLabel()
{
    QWidget *widget = new QWidget();    
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setMargin(2);
    QLabel *label = new QLabel(content);

    if(isSend)
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
    
    return widget; 
}