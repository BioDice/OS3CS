// OS3Client.cpp : Defines the entry point for the console application.
//
//#include <vld.h>
#include <string>
#include "Client.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


using namespace OS3CS;
volatile bool isRunning = true;
#if defined(_WIN32)

#include <windows.h>
#include <stdio.h>

BOOL WINAPI HandlerRoutine(_In_ DWORD dwCtrlType) {
	switch (dwCtrlType)
	{
	case CTRL_C_EVENT:
		isRunning = false;
		// Signal is handled - don't pass it on to the next handler
		return TRUE;
	default:
		// Pass signal on to the next handler
		return FALSE;
	}
}
#endif

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
#if defined(_WIN32)
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
#endif

	//wcin.imbue(std::locale("English_United States.437"));
	//wcout.imbue(std::locale("English_United States.437"));
	//SetConsoleOutputCP(CP_UTF8);
	DirectoryWriter * writer = new DirectoryWriter();
	writer->InitList();

	//setlocale(LC_ALL, "");
	Client client = Client();

	while (isRunning)
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
