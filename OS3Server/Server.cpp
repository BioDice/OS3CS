#include "stdafx.h"
#include "Server.h"

namespace OS3CS
{
	Server::Server(void)
	{

	}

	Server::~Server(void)
	{
		
	}

	void Server::handle(Socket *socket)
	{
		char response[257];
		cout << "Client connected!\r\n";
		socket->write("Yo");
		try
		{
			while (socket->readline(response, 256) > 0)
			{
				vector<string> command = vector<string>();
				cout << response;
				StrSplit(response, " ", command);


			}
		}
		catch (SocketException& ex)
		{
			cout << "Socket exception occured" << endl;
		}
	}

	void Server::listen(int port)
	{
		ServerSocket serverSocket(port);

		cout << "Server is listening..\r\n";

		while (Socket *socket = serverSocket.accept())
		{
			cout << "New connection established..\r\n";

			this->handle(socket);

			delete socket;

			cout << "Server is listening..\r\n";
		}
	}
}