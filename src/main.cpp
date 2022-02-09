#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "include/ChatWindow.hpp"

int chatAmount = 2;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    srand(time (0));

    for(int i=0;i<argc;i++)
    {
        if(strcmp(argv[i],"-a")==0)
            chatAmount = atoi(argv[i+1]);
    }

    for(int i=0;i<chatAmount;i++)    
        new ChatWindow(i==0);

    return app.exec();
}