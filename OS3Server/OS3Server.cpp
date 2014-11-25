// OS3Server.cpp : Defines the entry point for the console application.
//
#include <string>
#include "Server.h"

using namespace OS3CS;
int main()
{
	//wcin.imbue(std::locale("English_United States.437"));
	//wcout.imbue(std::locale("English_United States.437"));
	//setlocale(LC_ALL, "");
	//SetConsoleOutputCP(CP_UTF8);
	DirectoryWriter *writer = new DirectoryWriter();
	writer->InitList();
	Server *server = new Server();
	server->listen(100);

	return 0;
}