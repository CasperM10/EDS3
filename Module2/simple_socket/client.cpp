#include "protocol.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

void connect(int socketFd)
{
    if (socketFd == -1)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PortNumber);

    int result = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);
    if (result != 1)
    {
        perror("could not convert ip address to network address structure");
        exit(EXIT_FAILURE);
    }
    else
    {
        result = connect(socketFd, (struct sockaddr*)&sa, sizeof sa);
        if (result < 0)
        {
            perror("connect failed");
            close(socketFd);
            exit(EXIT_FAILURE);
        }
	}
}

void disconnect(int socketFd)
{
	if (shutdown(socketFd, SHUT_RDWR) < 0)
    {
        perror("shutdown failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    close(socketFd);
    //return EXIT_SUCCESS;
}

void sendMessage(std::string message, int socketFd)
{
	std::string text = message;
    size_t nrBytes = send(socketFd, text.c_str(), text.length(), 0);
    if (nrBytes != text.length())
    {
        std::cout << "not everything is sent (" << nrBytes << "/" << text.length() << " bytes sent)\n";
    }
        
    const int BufferSize = 100;
    char buffer[BufferSize];
    int nrBytes2 = read(socketFd, buffer, BufferSize - 1);
    if (nrBytes2 >= 0)
    {
        buffer[nrBytes2] = '\0';
        if(strcmp(buffer, "Acknowledge") == 0)
        {
			std::cout << "Message Sent!";
		}
    }
}

static void showMenu()
{
    std::cout << ("\n\nClient menu\n");
    std::cout << ("===============\n");
    std::cout << ("(1) Connect to server\n");
    std::cout << ("(2) Disconnect from server\n");
    std::cout << ("(3) Send Message\n");
    std::cout << ("(4) Exit\n");
    std::cout << ("Choice : ");
}

int main(void)
{
	int socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	bool quit = false;

    while (!quit)
    {
        char choice = '\0';
        showMenu();
        std::cin >> choice;
        std::cin.ignore();
        std::string input = "";
        switch (choice)
        {
        case '1' :
            connect(socketFd);
            break;
        case '2' :
            disconnect(socketFd);
            return 0;
            break;
        case '3' :
			std::cout << "What would you like to send?" << std::endl << "Message: ";
			
			std::cin >> input;
            sendMessage(input, socketFd);
            break;
        case '4' :
            quit = true;
            break;
        default:
            std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
            break;
        }
    }    
    return 0;    
}
