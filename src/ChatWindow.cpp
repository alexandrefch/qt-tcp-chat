#include "include/ChatWindow.hpp"

ChatWindow::ChatWindow(bool isServer)
{
    setWindowTitle(WINDOW_TITLE);
    setFixedSize(WINDOW_SIZE, WINDOW_SIZE);

    inputWidget = new InputWidget(54);
    convWidget  = new ConversationWidget();

    if( isServer )
        tcpSocket = new TcpServer(4242);
    else
        tcpSocket = new TcpClient(4242);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);
    verticalLayout->addWidget(convWidget,99);
    verticalLayout->addWidget(inputWidget,1);

    connect(
        inputWidget,SIGNAL(sendMessage(QString)),
        this,SLOT(sendMessage(QString))
        );

    connect(
        tcpSocket,SIGNAL(onReceiveMessage(QString)),
        this,SLOT(receiveMessage(QString))
        );

    generateWord();
    show();
}

ChatWindow::~ChatWindow()
{
    
}

void ChatWindow::generateWord()
{
    std::ifstream wordsFile("ressource/words.txt");
    std::string   line;
    int      count;
    int      random;
    int      i = 0;

    getline (wordsFile, line);
    count = atoi(line.c_str());
    random = std::rand()%count;

    while (getline (wordsFile, line)) {
        if(i++==random)
        {
            word = line;
            break;
        }
    }

    QString message = QString::fromUtf8(("Votre mot secret est : \'"+word+"\'").c_str());
    convWidget->displayMessage(new Message(message, MessageType::SEND));
    wordsFile.close();
}

void ChatWindow::closeEvent(QCloseEvent *event)
{
    tcpSocket->close();
}

void ChatWindow::receiveMessage(QString text)
{
    convWidget->displayMessage(new Message(text, MessageType::RECEIVE));
}

void ChatWindow::sendMessage(QString text)
{
    tcpSocket->sendMessage(text);
    convWidget->displayMessage(new Message(text, MessageType::SEND));
}