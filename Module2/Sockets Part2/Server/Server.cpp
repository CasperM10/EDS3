#include "protocol.h"
#include "Server.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

Server::Server()
{
	Listen();
}

Server::~Server()
{
	close(communicationFd);
	close(listenFd);
}

void Server::Listen()
{
	listenFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenFd < 0)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PortNumber);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenFd, (struct sockaddr*)&sa, sizeof sa) < 0)
    {
        perror("bind failed");
        close(listenFd);
        exit(EXIT_FAILURE);
    }

    if (listen(listenFd, 10) < 0)
    {
        perror("listen failed");
        close(listenFd);
        exit(EXIT_FAILURE);
    }
}

void Server::Accept()
{
	communicationFd = accept(listenFd, NULL, NULL);
    if (communicationFd < 0)
    {
        perror("accept failed");
        close(listenFd);
        exit(EXIT_FAILURE);
    }
}

void Server::ReadMessage()
{
	const int BufferSize = 100;
	char buffer[BufferSize];
	int nrBytes;
	do
		{
			nrBytes = read(communicationFd, buffer, BufferSize - 1);
			if (nrBytes > 0)
			{
				buffer[nrBytes] = '\0';
				std::cout << "received " << nrBytes << " bytes: " << buffer << std::endl;
			}
		} while(nrBytes > 0);
	if (shutdown(communicationFd, SHUT_RDWR) < 0)
	{
		perror("shutdown failed");
		close(communicationFd);
		close(listenFd);
		exit(EXIT_FAILURE);
	}
    close(communicationFd);
}

void Server::SendMessage(std::string message)
{
	if(message.length() > 0)
	{
		send(communicationFd, message.c_str(), message.length(), 0);
	}
}

void Server::ReadFile(char* filename)
{
	int length = 512;
	char *revbuf = new char[length];
	char* fr_name = filename;
    FILE *fr = fopen(fr_name, "a");
    if(fr == NULL)
        printf("File %s Cannot be opened file on server.\n", fr_name);
    else
    {
        bzero(revbuf, length); 
        int fr_block_sz = 0;
        while((fr_block_sz = recv(communicationFd, revbuf, length, 0)) > 0) 
        {
            int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
            if(write_sz < fr_block_sz)
            {
                perror("File write failed on server.\n");
            }
            bzero(revbuf, length);
            if (fr_block_sz == 0 || fr_block_sz != 512) 
            {
                break;
            }
        }
        if(fr_block_sz < 0)
        {
            if (errno == EAGAIN)
            {
                printf("recv() timed out.\n");
            }
            else
            {
                fprintf(stderr, "recv() failed due to errno = %d\n", errno);
                exit(1);
            }
        }
        printf("Ok received from client!\n");
        fclose(fr); 
	}
	delete[] revbuf;
}

bool Server::CanISendFile()
{
	if (listenFd < 0)
    {
        perror("listenSocket < 0");
        return false;
    }
    if (communicationFd < 0)
    {
        perror("commFd < 0");
        return false;
    }
    if (shutdown(communicationFd, SHUT_RDWR) < 0)
	{
		perror("shutdown failed");
		return false;
	}
	return true;
}
