#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
	private:
	int socketFd;
	
	void Connect();
	
	public:
	Client();
	~Client();
	
	void Disconnect();
	void SendMessage(std::string);
	void SendFile(char*);
	void ShowClientMenu();
};

#endif
