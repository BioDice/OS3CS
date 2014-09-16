#include "stdafx.h"
#include "Server.h"

namespace OS3CS
{
	Server::Server(void)
	{
		inputFactory = InputFactory();
		inputFactory.Initialize();
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
				vector<string> input = vector<string>();
				cout << response;
				StrSplit(response, input, ' ');

				// Converts the characters to lower case
				for (int i = 0; i < input[0].length(); i++)
						input[0][i] = tolower(input[0][i]);
				
				InputHandler *inputHandler = InputFactory::CreateHandler(input[0]);
				if (inputHandler != NULL)
				{
					inputHandler->Process(socket);
				}
				else
				{
					cout << " - Unknown Command\r\n";
					socket->writeline("Unknown Command\r\n");
				}
				/*
				if (input[0] == "info")
				{
					socket->writeline("Craptastic Server\r\nVersion: -0.1\r\n");
				}
				else if (input[0] == "exit")
				{
					socket->writeline("Thank you for using Craptastic Server\r\nWe hope we never see you again. BYE!");
					socket->close();
					break;
				}
				*/
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