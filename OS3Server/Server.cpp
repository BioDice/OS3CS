#include "stdafx.h"
#include "Server.h"

namespace OS3CS
{
	Server::Server(void)
	{
		inputFactory = new ServerFactory();
		inputFactory->Initialize();
	}

	Server::~Server(void)
	{
		
	}

	void Server::handle(Socket *socket)
	{
		char response[257];
		cout << "Client connected!\r\n";
		socket->writeline("Welcome to this ultra pro *cough* Server");
		socket->write("\n");
		try
		{
			while (socket->readline(response, 256) > 0)
			{
				vector<string> segments = vector<string>();
				
				StrSplit(response, segments, ' ');

				// Converts the characters to lower case
				for (int i = 0; i < segments[0].length(); i++)
					segments[0][i] = tolower(segments[0][i]);
				
				InputHandler *inputHandler = inputFactory->CreateHandler(segments[0]);
				if (inputHandler != NULL)
				{
					cout << response << endl;
					inputHandler->Process(socket, response);
				}
				else
				{
					ostringstream resp;
					resp << response << " - Unknown Command\r\n";
					cout << resp.str();
					socket->writeline(resp.str());
				}
				delete inputHandler;
			}
		}
		catch (SocketException& ex)
		{
			cout << "Socket exception occured: " << endl;
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
			cout << "Client is disconnected\r\n";
			cout << "Server is listening..\r\n";
		}
	}
}