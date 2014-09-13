// OS3Server.cpp : Defines the entry point for the console application.
//
#include <string>
#include "Server.h"

using namespace OS3CS;

int main()
{
	Server *server = new Server();
	server->listen(100);

	return 0;
}