#include <QApplication>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include "include/ChatWindow.hpp"

/**
 * @brief Entry point of the program, here we read all launch arguments,
 *        If we find sommething like '-a int' a is for amount and int will
 *        be the amount of chat window
 * 
 * @param argc char array of launch argument
 * @param argv lenght of char array
 * @return int 
 */
int main(int argc, char *argv[])
{
    int chatAmount = 2;

    QApplication app(argc, argv);
    srand(time (0));

    for(int i=0;i<argc;i++)
    {
        if(strcmp(argv[i],"-a")==0)
        {
            int value = atoi(argv[i+1]);
            if(value > chatAmount)
                chatAmount = value;
        }
    }

    // Create x window where x is chatAmount
    // the first window is a server otherwise it's a client
    for(int i=0;i<chatAmount;i++)
    {
        new ChatWindow(i==0);
    }

    return app.exec();
}