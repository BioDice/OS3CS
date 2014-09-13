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
		cout << "Client connected!";
		socket->write("Yo");

		while (socket->readline(response, 256) > 0)
		{
			cout << response;
		}
	}

	void Server::listen(int port)
	{
		ServerSocket serverSocket(port);

		cout << "Server is listening..";

		while (Socket *socket = serverSocket.accept())
		{
			cout << "New connection established..";

			this->handle(socket);

			delete socket;

			cout << "Server is listening..";
		}
	}
}