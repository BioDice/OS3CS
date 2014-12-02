// OS3Server.cpp : Defines the entry point for the console application.
//
#include <vld.h>
#include <string>
#include "Server.h"

using namespace OS3CS;

#if defined(_WIN32)

#include <windows.h>
#include <stdio.h>

volatile bool isRunning = true;
Server *server;

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		printf("Ctrl-C event\n\n");
		delete server;
		return(0);

		// CTRL-CLOSE: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		//Beep(600, 200);
		printf("Ctrl-Close event\n\n");
		return(TRUE);

		// Pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		//Beep(900, 200);
		printf("Ctrl-Break event\n\n");
		return FALSE;

	case CTRL_LOGOFF_EVENT:
		//Beep(1000, 200);
		printf("Ctrl-Logoff event\n\n");
		return FALSE;

	case CTRL_SHUTDOWN_EVENT:
		//Beep(750, 500);
		printf("Ctrl-Shutdown event\n\n");
		return FALSE;

	default:
		return FALSE;
	}
}
#endif

int main()
{
	//wcin.imbue(std::locale("English_United States.437"));
	//wcout.imbue(std::locale("English_United States.437"));
	//setlocale(LC_ALL, "");
	//SetConsoleOutputCP(CP_UTF8);

	/*if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
		printf("\nERROR: Could not set control handler");
		return 1;
	}*/
#if defined(_WIN32)
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{

	}
	else
	{
		printf("\nERROR: Could not set control handler");
		return 1;
	}
#endif
	try
	{
		DirectoryWriter *writer = new DirectoryWriter();
		writer->InitList();
		delete writer;

	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	server = new Server();
	server->listen(2500);
	delete server;

	return 0;
}

