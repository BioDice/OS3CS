// OS3Client.cpp : Defines the entry point for the console application.
//

#include <string>
#include "Client.h"

using namespace OS3CS;

void getConnectionDetails(Client& client)
{
	//cout << "enter host port" << endl;
	string str = "localhost";
	//string str = "84.105.106.236";
	char *adress = (char*)str.c_str();
	client.connect(adress,100);
}

int main()
{
	//wcin.imbue(std::locale("English_United States.437"));
	//wcout.imbue(std::locale("English_United States.437"));
	//SetConsoleOutputCP(CP_UTF8);
	DirectoryWriter * writer = new DirectoryWriter();
	writer->InitList();

	writer->WriteNode("newfile","randomdir");
	writer->WriteNode("file23490", "woopdir");
	writer->UpdateNode("newfile","renamedlol");
	writer->DeleteNode("renamedlol");

	//setlocale(LC_ALL, "");
	Client client = Client();
	getConnectionDetails(client);
	
	return 0;
}
