#include "Server.h"

using namespace std;

int main(void)
{
	bool quit = false;
	Server* server = new Server();
	std::cout << "Connected";
	while(!quit)
	{
		server->Accept();
		server->ReadMessage();
		
	}
	return 0;
}
