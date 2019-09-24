#include "Client.h"
#include "protocol.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

Client::Client()
{
	Connect();
}

Client::~Client()
{
	Disconnect();
}

void Client::Connect()
{
	socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
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
        std::cout << "Connected";
	}
}

void Client::Disconnect()
{
	if (shutdown(socketFd, SHUT_RDWR) < 0)
    {
        perror("shutdown failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    close(socketFd);
    std::cout << "Disconnected";
}

void Client::SendMessage(std::string message)
{
	std::string text = message;
    size_t nrBytes = send(socketFd, text.c_str(), text.length(), 0);
    if (nrBytes != text.length())
    {
        std::cout << "not everything is sent (" << nrBytes << "/" << text.length() << " bytes sent)\n";
    }
    std::cout << "Message Sent";
}

void Client::SendFile(char* filename)
{
	int length = 512;
	char* fs_name = filename;
    char *sdbuf = new char[length]; 

    printf("[Client] Sending %s to the Server... ", fs_name);
    FILE *fs = fopen(fs_name, "r");
    if(fs == NULL)
    {
        printf("ERROR: File %s not found.\n", fs_name);
        exit(1);
    }

    bzero(sdbuf, length); 
    int fs_block_sz;
    while((fs_block_sz = fread(sdbuf, sizeof(char), length, fs)) > 0)
    {
        if(send(socketFd, sdbuf, fs_block_sz, 0) < 0)
        {
            fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
            break;
        }
        bzero(sdbuf, length);
    }
    printf("Ok File %s from Client was Sent!\n", fs_name);
    delete[] sdbuf;
}

void Client::ShowClientMenu()
{
    std::cout << ("\n\nClient menu\n");
    std::cout << ("===============\n");
    std::cout << ("(1) Can I Send File?\n");
    std::cout << ("(2) Send File\n");
    std::cout << ("(3) Request File\n");
    std::cout << ("(4) Delete File\n");
    std::cout << ("(5) Exit\n");
    std::cout << ("Choice : ");
}
