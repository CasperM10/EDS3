#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server
{
	private:
	int listenFd;
	int communicationFd;
	
	void Listen();
	
	public:
	Server();
	~Server();
	
	void Accept();
	void ReadMessage();
	void SendMessage(std::string);
	void ReadFile(char*);
	bool CanISendFile();
};





#endif
