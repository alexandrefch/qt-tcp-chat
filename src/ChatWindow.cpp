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
        inputWidget,SIGNAL(sendMessage(Message)),
        this,SLOT(sendMessage(Message))
        );

    connect(
        tcpSocket,SIGNAL(onReceiveMessage(Message)),
        this,SLOT(receiveMessage(Message))
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
    convWidget->displayMessage(Message(message, true, MessageType::PROGRAM));
    wordsFile.close();
}

void ChatWindow::checkWord(QString text)
{
    const unsigned short  word_len = word.length();
    const unsigned short  text_len = text.length();
    const char           *word_c   = word.c_str();
    const char           *text_c   = text.toStdString().c_str();
    char                 *mask_c   = new char[word_len];

    // Init mask to "____" of word length
    for(int i=0;i<word_len;i++)
        mask_c[i] = '_';

    // 
    for(int i=0;i<text_len;i++)
    {
        for(int j=0;j<word_len;j++)
        {
            if(mask_c[j] == '_' && text_c[i]==word_c[j])
                mask_c[j] = word_c[j];
        }
    }

    Message msg(
        QString::fromUtf8(mask_c),
        true,
        MessageType::PROGRAM
    );

    this->sendMessage(msg);
}

void ChatWindow::closeEvent(QCloseEvent *event)
{
    tcpSocket->close();
}

void ChatWindow::receiveMessage(Message msg)
{
    std::cout << msg.getContent().toStdString() << std::endl;
    convWidget->displayMessage(msg);
    if(msg.getType()==MessageType::USER)
        checkWord(msg.getContent());
}

void ChatWindow::sendMessage(Message msg)
{
    tcpSocket->sendMessage(msg);
    convWidget->displayMessage(msg);
}