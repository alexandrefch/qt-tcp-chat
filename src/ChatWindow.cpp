#include "include/ChatWindow.hpp"

/**
 * @brief Construct a new Chat Window:: Chat Window object
 *        Init server or client on port 4242 and crate Vertical layout
 *        with on top the message box and input field under it       
 *        Also generate a first secret word 
 * 
 * @param isServer bool to know is it's a server or a client
 */
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

/**
 * @brief Destroy the Chat Window:: Chat Window object
 * 
 */
ChatWindow::~ChatWindow()
{
    
}

/**
 * @brief Generate a random word form the file 'ressource/word.txt'
 */
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

/**
 * @brief display secret word hidden by '_' char, unhide every letter of the secret
 *        word that is in the text received  
 * 
 * @see wordle game
 * @param text to compare to the secret word
 */
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

/**
 * @brief OnCloseEvent close tcp connection
 * 
 * @param event 
 */
void ChatWindow::closeEvent(QCloseEvent *event)
{
    tcpSocket->close();
}

/**
 * @brief function call everytime that network receive a message
 * 
 * @param msg 
 */
void ChatWindow::receiveMessage(Message msg)
{
    convWidget->displayMessage(msg);
    if(msg.getType()==MessageType::USER)
        checkWord(msg.getContent());
}

/**
 * @brief function call everytime that we want to send message on network
 * 
 * @param msg 
 */
void ChatWindow::sendMessage(Message msg)
{
    tcpSocket->sendMessage(msg);
    convWidget->displayMessage(msg);
}