// OS3Client.cpp : Defines the entry point for the console application.
//

#include <string>
#include "Client.h"

using namespace OS3CS;

void getConnectionDetails(Client& client)
{
	cout << "Please enter an IPaddress and a port in the following syntax:" << endl;
	cout << "[host] [port]" << endl;
	string response;
	getline(cin, response);

	if (response != "")
	{
		vector<string> segments = vector<string>();
		FormatConnectionString(response, segments, 2);
		
		if (segments.size() != 2)
		{
			cout << "Syntax error..." << endl;
			cout << "Please use [host] [port]" << endl;
			return;
		}
		//string str = "localhost";
		////string str = "84.105.106.236";
		//char *adress = (char*)str.c_str();
		client.connect(segments[0].c_str(), stoi(segments[1]));
	}

	return;
}

int main()
{
	//wcin.imbue(std::locale("English_United States.437"));
	//wcout.imbue(std::locale("English_United States.437"));
	//SetConsoleOutputCP(CP_UTF8);
	DirectoryWriter * writer = new DirectoryWriter();
	writer->InitList();

	//writer->WriteNode("newfile","randomdir");
	//writer->WriteNode("file23490", "woopdir");
	//writer->UpdateNode("newfile","renamedlol");
	//writer->DeleteNode("renamedlol");

	//setlocale(LC_ALL, "");
	Client client = Client();

	while (1)
	{
		try
		{
			getConnectionDetails(client);
		}
		catch (SocketException& ex)
		{
			std::cout << "Connection lost..." << endl;
		}
		catch (invalid_argument& ex)
		{
			std::cout << "Invalid argument" << endl;
		}
		catch (out_of_range& ex)
		{
			std::cout << "Port out of range" << endl;
		}
		catch (runtime_error& ex)
		{
			std::cout << ex.what() << endl;
		}
	}
	
	
	return 0;
}
