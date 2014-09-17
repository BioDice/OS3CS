#include "Client.h"
#include "../shared/Socket.h"

namespace OS3CS
{
    Client::Client(void)
    {
		inputFactory = InputFactory();
		inputFactory.InitializeClient();
    }


    Client::~Client(void)
    {
    }

    void Client::connect(const char* adress, int port)
    {
        Socket * s = NULL;

        try
        {
            s = new ClientSocket(adress,port);
			cout << "Created ClientSocket\r\n";
		
			listenToSocket(s);
        
			string input;
			char response[256];
			while (getline(cin, input))
			{
				vector<string> segments = vector<string>();
				cout << response << endl;
				StrSplit(response, segments, ' ');

				// Converts the characters to lower case
				for (int i = 0; i < segments[0].length(); i++)
					segments[0][i] = tolower(segments[0][i]);

				InputHandler *inputHandler = InputFactory::CreateHandler(segments[0]);
				if (inputHandler != NULL)
					inputHandler->Process(s);
				else
					InputFactory::CreateHandler("resp")->Process(s);
				delete inputHandler;
				/*
				s->writeline(input);
				while (s->readline(response, 256) > 0)
				{
					cout << response << endl;
				}*/
			}

			delete s;
		}
		catch (runtime_error& ex)
		{
			delete s;
			throw(ex);
		}
    }

    void Client::listenToSocket(Socket* socket)
    {
        char line[256 + 1];

        while (socket->readline(line, 257) > 0)
        {
            cout << line << endl;
        }
    }
}
