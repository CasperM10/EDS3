#include "Client.h"

using namespace std;

#include <iostream>

int main(void)
{
	bool quit = false;
	Client* client = new Client();
	
	while(!quit)
	{
		//bool canSend = false;
		client->ShowClientMenu();
		char choice = '\0';
		cin >> choice;
		cin.ignore();
	switch (choice)
        {
        case '1' :
			client->SendMessage("hello");
            break;
        case '2' :
            
            break;
        case '3' :
			
            break;
        case '4' :
            quit = true;
            break;
        default:
            std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
            break;
        }
	}
}
