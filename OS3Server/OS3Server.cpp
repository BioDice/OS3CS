// OS3Server.cpp : Defines the entry point for the console application.
//
#include <string>
#include "Server.h"

using namespace OS3CS;

#if defined(_WIN32)

#include <windows.h>
#include <stdio.h>

volatile bool isRunning = true;

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
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
#endif
	DirectoryWriter *writer = new DirectoryWriter();
	writer->InitList();
	Server *server = new Server();
	server->listen(2500);

	return 0;
}

