// OS3Client.cpp : Defines the entry point for the console application.
//

#include <string>
#include "Client.h"

using namespace OS3CS;

void getConnectionDetails(Client& client)
{
	//cout << "enter host port" << endl;
	string str = "84.105.106.236";
	char *adress = (char*)str.c_str();
	client.connect(adress,100);
}

int main()
{
	Client client = Client();
	getConnectionDetails(client);
	
	return 0;
}
